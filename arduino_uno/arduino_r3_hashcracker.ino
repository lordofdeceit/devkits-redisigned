#include <SHA256.h>

// Hash to crack
const char* targetHash = "5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8";

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial connection
}

void loop() {
  char password[8]; // Assume a maximum password length of 8 characters
  
  // Generate password combinations
  for (int i = 0; i < 100000000; i++) {
    snprintf(password, sizeof(password), "%08d", i); // Convert integer to a zero-padded string
    
    // Calculate the hash of the password
    SHA256 sha256;
    sha256.update(password, strlen(password));
    uint8_t* hash = sha256.finalize();

    // Convert the hash to a hexadecimal string
    char hashString[SHA256_SIZE * 2 + 1];
    for (int j = 0; j < SHA256_SIZE; j++) {
      sprintf(&hashString[j * 2], "%02x", hash[j]);
    }

    // Compare the generated hash with the target hash
    if (strcmp(hashString, targetHash) == 0) {
      Serial.print("Password found: ");
      Serial.println(password);
      break;
    }
  }

  // Delay to prevent the loop from running too fast
  delay(1000);
}

