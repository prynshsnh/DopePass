#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void login();

void key_generator(char *, int);

void cipher(char[], char[], char[]);

void save_password();

void open_password();

void display_password();

void display_references();

void erase_vault();

void reset_admin_password();

char password[100], reference[100], encrypted[100], key[100], decrypted[100], log_pass[100];

char log_pass_set[100] = "admin";

int main()
{
	login();

	int choice;
	puts("\n               ********* WELCOME TO DOPE_PASS PASSWORD MANAGER *********\n\nEnter your choice...\n");
	do
	{
		puts("1. Save a new password\n2. Open a saved password\n3. Display all the references\n4. Erase the vault\n5. Reset LogIn Password\n6. Exit the password manager");
		printf("\nInput Console> ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			save_password();
			break;
		case 2:
			open_password();
			break;
		case 3:
			display_references();
			break;
		case 4:
			erase_vault();
			break;
		case 5:
			reset_admin_password();
			break;
		case 6:
			printf("\nProgram is terminating...");
			exit(0);
		default:
			puts("Enter a valid choice!");
			break;
		}

	} while (1);
}

void login()
{
	printf("ENTER YOUR LOGIN PASSWORD: ");
	scanf("%s", log_pass);
	if (strcmp(log_pass, log_pass_set) != 0)
	{
		printf("Wrong Password! Try Again.");
		exit(0);
	}
}

void key_generator(char *key, int n)
{
	srand((unsigned int)(time(NULL)));
	int index = 0;

	char strings[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	for (index = 0; index < n; index++)
	{
		key[index] = strings[rand() % (sizeof strings - 1)];
	}
	key[index] = '\0';
}

void cipher(char *input, char *output, char *key)
{
	int i;
	for (i = 0; i < strlen(input); i++)
	{
		output[i] = input[i] ^ key[i];
	}
	output[i] = '\0';
}

void save_password()
{
	printf("ENTER YOUR REFERENCE (A reference is an identifying keyword for your saved password.)\n");
	printf("e.g. If I want to save my amazon account password I would like to give my reference as 'amazon'");
	printf("\nInput Console> ");
	scanf("%s", reference);
	printf("ENTER YOUR PASSWORD \n");
	printf("\nInput Console> ");
	scanf("%s", password);

	key_generator(key, strlen(password));

	cipher(password, encrypted, key);
	FILE *fp;
	fp = fopen("vault.txt", "a");
	if (fp == NULL)
		puts("\nFile failed to open!\n");
	else
	{
		fprintf(fp, "%s %s %s", reference, encrypted, key);
		fputs("\n", fp);
	}
	fclose(fp);

	puts("\nYOUR PASSWORD HAS BEEN ENCRYPTED AND SAVED.\n");
}

void open_password()
{
	char input_reference[40];
	printf("ENTER REFERENCE WORD OF YOUR PASSWORD: ");
	scanf("%s", input_reference);

	FILE *fp;
	fp = fopen("vault.txt", "r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		for (int i = 0; i < 40; i++)
		{
			fscanf(fp, "%s %s %s \n", reference, encrypted, key);
			if (strcmp(reference, input_reference) == 0)
				break;
		}
	}

	cipher(encrypted, decrypted, key);

	printf("\nDECRYPTED PASSWORD: %s \n\n", decrypted);
}

void display_references()
{
	puts("The references are:");
	FILE *fp;
	fp = fopen("vault.txt", "r");
	if (fp == NULL)
		puts("\nFile failed to open!\n");
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s \n", reference, encrypted, key);
			puts(reference);
		}
	}
}

void erase_vault()
{
	if (remove("vault.txt") == 0)
		printf("\nPASSWORD VAULT DELETED SUCCESSFULLY.\n\n");
	else
		printf("\nUnable to delete the vault!\n");
}

void reset_admin_password()
{
	char ch1[50], ch2[50];
	printf("Enter Old Password: ");
	scanf("%s", ch1);
	printf("Enter new Password: ");
	scanf("%s", ch2);
	if (strcmp(ch1, log_pass_set) == 0)
	{
		strcpy(log_pass_set, ch2);
		printf("\nPASSWORD CHANGED SUCCESSFULLY!\n");
	}
	else
	{
		printf("\nSomething went Wrong! Try Again.\n");
	}
}