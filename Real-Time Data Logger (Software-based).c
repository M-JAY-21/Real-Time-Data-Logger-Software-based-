#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(x) Sleep(x) // Windows uses milliseconds
#else
#include <unistd.h>
#define SLEEP(x) sleep(x) // Linux/Mac uses seconds
#endif

float generateTemperature() {
    return ((rand() % 4001) / 100.0) - 10.0; // -10.00°C to 30.00°C
}

float generateHumidity() {
    return ((rand() % 8001) / 100.0) + 20.0; // 20.00% to 100.00%
}

void logData(FILE *file, float temp, float humidity) {
    time_t t;
    struct tm *tm_info;
    char timestamp[30];

    time(&t);
    tm_info = localtime(&t);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(file, "%s | Temp: %.2f °C | Humidity: %.2f %%\n", timestamp, temp, humidity);
    fflush(file); // Ensure data is written immediately

    printf("%s | Temp: %.2f °C | Humidity: %.2f %%\n", timestamp, temp, humidity);
}

int main() {
    FILE *file = fopen("datalog.txt", "a");
    if (file == NULL) {
        perror("❌ Error opening file");
        return 1;
    }

    srand(time(NULL)); // Random seed

    printf("📡 Starting Real-Time Data Logger...\n");
    printf("Press Ctrl+C to stop.\n\n");

    while (1) {
        float temp = generateTemperature();
        float humidity = generateHumidity();

        logData(file, temp, humidity);

        SLEEP(2); // Log every 2 seconds
    }

    fclose(file);
    return 0;
}
