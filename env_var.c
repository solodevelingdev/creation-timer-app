#include "env_var.h"

void load_env_file() {
    FILE *file = fopen(".env", "r");
    if (!file) {
        fprintf(stderr, "Warning: .env file not found! Using system defaults.\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Skip empty lines or lines starting with comments (#)
        if (line[0] == '\0' || line[0] == '#') continue;

        // Split the line at the '=' sign
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key && value) {
            // Save it into the app's runtime environment memory
            setenv(key, value, 1);
        }
    }
    fclose(file);
}