#include <Crypto.h>
#include <SHA256.h>

// Hash to crack
const char* targetHash = "2ab963e9b43f459c275c8d70f8b93f9e9b4bf4d04a8fc92f7f0ad0b76b2e105c";
const char* salt = "somesalt";

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial connection
}

void loop() {
  char password[8]; // Assume a maximum password length of 8 characters
  
  // Generate password combinations
  for (int i = 0; i < 100000000; i++) {
    snprintf(password, sizeof(password), "%08d", i); // Convert integer to a zero-padded string

    // Combine the password with the salt
    char saltedPassword[sizeof(password) + strlen(salt) + 1];
    snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", salt, password);

    // Calculate the hash of the salted password
    SHA256 sha256;
    sha256.reset();
    sha256.update((uint8_t*)saltedPassword, strlen(saltedPassword));
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

