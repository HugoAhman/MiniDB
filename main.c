#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pokemon
{
    char pokemonType[50];    // Pokémonens typ, t.ex. "Fire", "Water"
    char pokemonName[50];    // Pokémonens namn, t.ex. "Charmander"
    char evolutionStage[20]; // Utvecklingsstadiet, t.ex. "första", "andra", "legendary"
    struct Pokemon *next;
} Pokemon;

// Funktion för att spara listan av Pokémon till en fil
void save_to_file(Pokemon *head)
{
    FILE *file = fopen("pokemoninfo.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // Går igenom hela listan av Pokémon och skriver varje Pokémon till filen
    Pokemon *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s %s %s\n", current->pokemonType, current->pokemonName, current->evolutionStage);
        current = current->next; // Går till nästa Pokémon i listan
    }

    fclose(file);
}

// Funktion för att ladda Pokémon-listan från en fil
Pokemon *load_from_file()
{
    FILE *file = fopen("pokemoninfo.txt", "r");
    if (file == NULL)
    {
        printf("No previous data found.\n");
        return NULL;
    }

    Pokemon *head = NULL;
    Pokemon *current = NULL;

    while (!feof(file))
    {
        Pokemon *newPokemon = malloc(sizeof(Pokemon));
        // Läser in data från filen och kontrollerar om läsningen lyckades
        if (fscanf(file, "%s %s %s", newPokemon->pokemonType, newPokemon->pokemonName, newPokemon->evolutionStage) == 3)
        {
            newPokemon->next = NULL;
            if (head == NULL)
            {
                head = newPokemon; // Om listan är tom, sätt den nya Pokémon som första element
                current = head;
            }
            else
            {
                current->next = newPokemon; // Annars, lägg till den nya Pokémon i slutet av listan
                current = current->next;
            }
        }
        else
        {
            free(newPokemon);
        }
    }

    fclose(file);
    return head;
}

// Funktion för att lägga till en ny Pokémon till listan
void add_pokemon(Pokemon **head, char *pokemonType, char *pokemonName, char *evolutionStage)
{
    Pokemon *newPokemon = malloc(sizeof(Pokemon));
    // Kopierar de givna värdena till den nya Pokémonens attribut
    strcpy(newPokemon->pokemonType, pokemonType);
    strcpy(newPokemon->pokemonName, pokemonName);
    strcpy(newPokemon->evolutionStage, evolutionStage);
    newPokemon->next = *head;
    *head = newPokemon;
}

// Funktion för att skriva ut alla Pokémon i listan
void print_pokemons(Pokemon *head)
{
    Pokemon *current = head;
    while (current != NULL)
    {
        // Skriver ut Pokémonens typ, namn och utvecklingsstadium
        printf("Type: %s, Name: %s, Evolution Stage: %s\n", current->pokemonType, current->pokemonName, current->evolutionStage);
        current = current->next;
    }
}

// Funktion för att frigöra minnet som använts av listan
void free_memory(Pokemon *head)
{
    Pokemon *current = head;
    while (current != NULL)
    {
        Pokemon *next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    Pokemon *head = load_from_file(); // Laddar listan från filen vid start

    int choice; // Variabel för att hålla användarens menyval
    char pokemonType[50];
    char pokemonName[50];
    char evolutionStage[20];

    while (1) // En oändlig loop som bryts när användaren väljer att avsluta
    {
        // Visar en meny för användaren
        printf("\n1. Add a Pokémon\n2. View all Pokémon\n3. Save and exit\nChoose an option: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1)
        {
            // Användaren vill lägga till en ny Pokémon
            printf("Enter Pokémon type: ");
            scanf("%s", pokemonType);
            printf("Enter Pokémon name: ");
            scanf("%s", pokemonName);
            printf("Enter evolution stage: ");
            scanf("%s", evolutionStage);

            add_pokemon(&head, pokemonType, pokemonName, evolutionStage); // Lägger till den nya Pokémonen i listan
        }
        else if (choice == 2)
        {
            print_pokemons(head); // Visar alla Pokémons i listan
        }
        else if (choice == 3)
        {
            save_to_file(head); // Sparar listan till filen och avslutar programmet
            break;
        }
        else
        {
            printf("Invalid option. Please try again.\n"); // Felmeddelande om användaren gör ett ogiltigt val
        }
    }

    free_memory(head); // Frigör minnet som använts av listan innan programmet avslutas
    return 0;
}
