#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MEMORY_NAME "/saperlipopette"
#define BUFFER_SIZE 256

typedef struct{
    int id_number;
    int shutdown_status;
    char access_key[BUFFER_SIZE];
    char valve_status[BUFFER_SIZE];
    char selected_drink[BUFFER_SIZE];
} ConfigData;

int initialize_shared_memory(ConfigData **data){
    int memory_fd = shm_open(MEMORY_NAME, O_RDWR, 0666);
    if (memory_fd == -1)
    {
        perror("Failed to open shared memory");
        return -1;
    }

    *data = mmap(NULL, sizeof(ConfigData), PROT_READ | PROT_WRITE, MAP_SHARED, memory_fd, 0);
    if (*data == MAP_FAILED)
    {
        perror("Failed to map shared memory");
        close(memory_fd);
        return -1;
    }

    return memory_fd;
}

void sync_shared_memory(ConfigData *data){
    if (msync(data, sizeof(ConfigData), MS_SYNC) == -1)
    {
        perror("Error syncing memory");
    }
}

void update_test_config(ConfigData *data){
    strcpy(data->access_key, "Znaba qrf fbheprf");
    strcpy(data->valve_status, "closed");
    strcpy(data->selected_drink, "water");

    sleep(5);
    strcpy(data->valve_status, "opened");
    strcpy(data->selected_drink, "water");
}

void set_valve_state(ConfigData *data, const char *state, const char *drink){
    if (strcasecmp(state, "opened") != 0 && strcasecmp(state, "close") != 0){
        printf("Invalid state. Use 'opened' or 'close'.\n");
        return;
    }

    strncpy(data->valve_status, state, BUFFER_SIZE - 1);
    data->valve_status[BUFFER_SIZE - 1] = '\0';

    strncpy(data->selected_drink, drink, BUFFER_SIZE - 1);
    data->selected_drink[BUFFER_SIZE - 1] = '\0';

    if (msync(data, sizeof(ConfigData), MS_SYNC) == -1)
    {
        perror("Failed to sync memory");
    }
    else
    {
        printf("Valve set to: %s\n", data->valve_status);
        printf("Selected drink: %s\n", data->selected_drink);
    }
}

void display_config(ConfigData *data){
    printf("ID: %d\n", data->id_number);
    printf("Shutdown status: %d\n", data->shutdown_status);
    printf("Valve: %s\n", data->valve_status);
    printf("Drink: %s\n", data->selected_drink);
}

void reset_config(ConfigData *data){
    strcpy(data->access_key, "Znaba qrf fbheprf");
    strcpy(data->valve_status, "closed");
    strcpy(data->selected_drink, "water");
    data->shutdown_status = 1;

    msync(data, BUFFER_SIZE, MS_SYNC);
    printf("Configuration reset to default.\n");
}

void open_valve(ConfigData *data){
    strcpy(data->valve_status, "opened");

    msync(data, BUFFER_SIZE, MS_SYNC);
    printf("Valve set to: %s\n", data->valve_status);
}

void select_drink(ConfigData *data){
    char drink[BUFFER_SIZE];
    printf("Select a drink: ");
    scanf("%s", drink);

    strncpy(data->selected_drink, drink, BUFFER_SIZE - 1);
    data->selected_drink[BUFFER_SIZE - 1] = '\0';

    msync(data, BUFFER_SIZE, MS_SYNC);
    printf("Drink selected: %s\n", data->selected_drink);
}

void close_shared_memory(ConfigData *data, int memory_fd){
    munmap(data, BUFFER_SIZE);
    close(memory_fd);
}

void override_password(ConfigData *data){
    strcpy(data->access_key, "Znaba qrf fbheprf");
    sync_shared_memory(data);
}

int main(){
    ConfigData *data;

    int shared_fd = initialize_shared_memory(&data);

    update_test_config(data);
    close_shared_memory(data, shared_fd);

    return 0;
}