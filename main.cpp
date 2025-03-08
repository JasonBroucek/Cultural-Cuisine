//program name: Final Project
//name: Jason Broucek
//date: 11/24/2024


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;
// Structure to represent a recipe with multiple attributes.
struct Recipe {
    string name;
    string cuisine;
    string region;
    string dietaryRestriction;
    int cookTime;
    string ingredients;
    string instructions;
    string culturalSignificance;
};
// Class that handles the cuisine discovery program.
class CuisineProgram {
private:
    vector<Recipe> recipes;// Vector to store all the recipes.

public:
    CuisineProgram() {
        ifstream file("recipes.txt"); // Open the file containing recipes.
        string line;

        if (file.is_open()) {
            // Read each line from the file and parse it into Recipe structure.
            while (getline(file, line)) {
                Recipe recipe;
                size_t pos = 0;
                int fieldIndex = 0;
                string token;

                vector<string> fields;
                while ((pos = line.find(',')) != string::npos) {
                    token = line.substr(0, pos);
                    fields.push_back(token);
                    line.erase(0, pos + 1);
                }
                fields.push_back(line);

                if (fields.size() >= 8) {
                    recipe.name = fields[0];
                    recipe.cuisine = fields[1];
                    recipe.region = fields[2];
                    recipe.dietaryRestriction = fields[3];
                    recipe.cookTime = stoi(fields[4]);
                    recipe.ingredients = fields[5];
                    recipe.instructions = fields[6];
                    recipe.culturalSignificance = fields[7];
                }

                recipes.push_back(recipe);
            }
            file.close();
        }
        else {
            cout << "Unable to open the file." << endl;
        }
    }
    // Check if the given cuisine type is valid.
    bool isValidCuisine(const string& cuisineType) {
        const vector<string> validCuisines = { "Italian", "Thai", "Mexican", "Japanese", "Middle Eastern", "American", "Chinese",  "Any" };
        return find(validCuisines.begin(), validCuisines.end(), cuisineType) != validCuisines.end();
    }
    // Check if the given dietary restriction is valid.
    bool isValidDietaryRestriction(const string& dietaryRestriction) {
        const vector<string> validRestrictions = { "Gluten Free", "Vegetarian", "None", "Any" };
        return find(validRestrictions.begin(), validRestrictions.end(), dietaryRestriction) != validRestrictions.end();
    }
    // Display recipes that match the user's preferences.
    void displayRecipes(const string& cuisineType, const string& dietaryRestriction, int maxCookTime) {
        bool found = false;
        cout << "\n--- Matching Recipes ---\n";
        for (const auto& recipe : recipes) {
            if ((recipe.cuisine == cuisineType || cuisineType == "Any") &&
                (recipe.dietaryRestriction == dietaryRestriction || dietaryRestriction == "Any") &&
                (recipe.cookTime <= maxCookTime)) {
                // Display the recipe's details.
                cout << "Recipe Name: " << recipe.name << endl;
                cout << "Cuisine: " << recipe.cuisine << endl;
                cout << "Region: " << recipe.region << endl;
                cout << "Cook Time: " << recipe.cookTime << " minutes" << endl;
                cout << "Ingredients: " << recipe.ingredients << endl;
                cout << "Instructions: " << recipe.instructions << endl;
                cout << "Cultural Significance: " << recipe.culturalSignificance << endl;
                cout << "----------------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No recipes found matching your criteria." << endl;
        }
    }

    void run() {
        string cuisineType;
        string dietaryRestriction;
        int maxCookTime;
        char choice;
        
        do {
            cout << "\n--- Cuisine Discovery Program ---\n";
            cout << "Please enter your preferences:\n";
            
            do {
                // Prompt user to select a valid cuisine type.
                cout << "1. Enter cuisine type (e.g., Italian, Thai, Mexican, Japanese, Middle Eastern, American, Chinese, German, or type 'Any' for all): ";
                getline(cin, cuisineType);
                if (!isValidCuisine(cuisineType)) {
                    cout << "Invalid input. Please enter a valid cuisine type.\n";
                }
            } while (!isValidCuisine(cuisineType));

            do {
                // Prompt user to select a valid dietary restriction.
                cout << "2. Enter dietary restriction (e.g., Gluten Free, Vegetarian, or type 'Any' for all options): ";
                getline(cin, dietaryRestriction);
                if (!isValidDietaryRestriction(dietaryRestriction)) {
                    cout << "Invalid input. Please enter a valid dietary restriction.\n";
                }
            } while (!isValidDietaryRestriction(dietaryRestriction));
            // Prompt user to input the maximum cook time in minutes.
            cout << "3. Enter maximum cook time (in minutes, e.g., 30): ";
            cin >> maxCookTime;
            cin.ignore();

            displayRecipes(cuisineType, dietaryRestriction, maxCookTime);
            // Ask the user if they want to search again.
            cout << "\nWould you like to search again? (y/n): ";
            cin >> choice;
            cin.ignore();
        } while (choice == 'y' || choice == 'Y');

        cout << "\nThank you for using the Cuisine Program!" << endl;
    }
};

int main() {
    CuisineProgram program;
    program.run();
    return 0;
}
