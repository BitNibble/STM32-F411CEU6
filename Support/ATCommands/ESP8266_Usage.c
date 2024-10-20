const char* command;

// Example: Connect to Wi-Fi
command = esp8266_cmd(5, "MySSID", "MyPassword");
printf("Command: %s", command);

// Example: Start TCP connection
command = esp8266_cmd(7, "192.168.1.1", "80");
printf("Command: %s", command);

/*** EOF ***/