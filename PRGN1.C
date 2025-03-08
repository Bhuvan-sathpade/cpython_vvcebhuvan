#include <stdio.h>
#include <string.h>

int minimumNumber(int n, char* password) {
    // Flags to check existence of required character types
    int hasDigit = 0, hasLower = 0, hasUpper = 0, hasSpecial = 0;
    
    // Check password characters using switch-case
    for (int i = 0; i < n; i++) {
        char ch = password[i];
        
        switch (1) {
            case 1:
                if (ch >= '0' && ch <= '9') {
                    hasDigit = 1;
                    break;
                }
            case 2:
                if (ch >= 'a' && ch <= 'z') {
                    hasLower = 1;
                    break;
                }
            case 3:
                if (ch >= 'A' && ch <= 'Z') {
                    hasUpper = 1;
                    break;
                }
            case 4:
                if (strchr("!@#$%^&*()-+", ch)) {
                    hasSpecial = 1;
                    break;
                }
        }
    }
    
    // Count missing character types
    int missingTypes = (!hasDigit) + (!hasLower) + (!hasUpper) + (!hasSpecial);
    
    // Ensure minimum length of 6
    return (n + missingTypes >= 6) ? missingTypes : (6 - n);
}

int main() {
    int n;
    char password[101]; // Assuming max length of password is 100
    
    scanf("%d", &n);
    scanf("%s", password);
    
    int result = minimumNumber(n, password);
    printf("%d\n", result);
    
    return 0;
}