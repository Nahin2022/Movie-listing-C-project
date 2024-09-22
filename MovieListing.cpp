#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Movie {
public:
    string Title;
    int ReleaseYear;
    float Rating;
    string Filming;
};

class Add {
    const string filename = "movie.csv";
    int getLastSerialNumber(const string& filename) {
        ifstream file(filename);
        string line;
        int serialNumber = 0;

        while (getline(file, line)) {
            stringstream ss(line);
            string serial;
            getline(ss, serial, ',');
            serialNumber = stoi(serial);
        }

        return serialNumber;
    }
public:
    void listing() {
        int serialNumber = getLastSerialNumber(filename) + 1;
        while (true) {
            Movie movie;

            cout << "Enter movie title (or type 'exit' to stop): ";
            getline(cin, movie.Title);
            if (movie.Title == "exit") {
                break;
            }

            cout << "Enter release year: ";
            cin >> movie.ReleaseYear;

            cout << "Enter rating: ";
            cin >> movie.Rating;

            cin.ignore(); // To ignore the newline character left by previous std::cin

            cout << "Enter filming location: ";
            getline(cin, movie.Filming);

            ofstream store;
            store.open(filename, ios::out | ios::app);

            if (store.is_open()) {
                // Write movie details to the file
                store << serialNumber << ","
                      << movie.Title << ","
                      << movie.ReleaseYear << ","
                      << movie.Rating << ","
                      << movie.Filming << "\n";
                store.close();
                serialNumber++;
            } else {
                cout << "Failed to open file.\n";
            }
        }
    }
};

class View {
    vector<Movie> readAllMovies(const string& filename) {
        vector<Movie> movies;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            Movie movie;
            string serial;

            getline(ss, serial, ','); // Read serial number (ignore it here)
            getline(ss, movie.Title, ',');
            ss >> movie.ReleaseYear;
            ss.ignore(); // Ignore the comma
            ss >> movie.Rating;
            ss.ignore(); // Ignore the comma
            getline(ss, movie.Filming, ',');

            movies.push_back(movie);
        }

        return movies;
    }

    void displayMovie(const Movie& movie) {
        cout << "Title: " << movie.Title << "\n";
        cout << "Release Year: " << movie.ReleaseYear << "\n";
        cout << "Rating: " << movie.Rating << "\n";
        cout << "Filming Location: " << movie.Filming << "\n\n";
    }

public:
    void show() {
        const string filename = "movie.csv";
        while (true) {
            cout << "Options:\nauto. View movies one by one\n"
                 << "search. View movie by name\n"
                 << "exit. Exit from view\n";
            string option;
            getline(cin, option);

            if (option == "exit") {
                break;
            } else if (option == "auto") {
                viewOneByOne(filename);
            } else if (option == "search") {
                viewByName(filename);
            } else {
                cout << "Invalid option, please try again.\n";
            }
        }
    }

    void viewOneByOne(const string& filename) {
        vector<Movie> movies = readAllMovies(filename);
        for (size_t i = 0; i < movies.size(); ++i) {
            displayMovie(movies[i]);
            cout << "Press Enter to see the next movie, 'b' to go back to menu.";
            string input;
            getline(cin, input);
            if (input == "b") {
                break;
            }
        }
    }

    void viewByName(const string& filename) {
        cout << "Enter movie name: ";
        string name;
        getline(cin, name);

        vector<Movie> movies = readAllMovies(filename);
        bool found = false;
        for (const auto& movie : movies) {
            if (movie.Title == name) {
                cout<<"Movie found!"<<endl;
                displayMovie(movie);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Movie not found.\n";
        }
    }
};


int main() {
    cout << "Type 'view' (to view existing list), 'add' (to add new movie), 'exit' (close the program)\n";
    string cmd;

    while (true) {
        cout << "Enter command: ";
        getline(cin, cmd);

        if (cmd == "exit") {
            cout << "Exit the application\n";
            break;
        } else if (cmd == "view") {
            View view;
            view.show();
        } else if (cmd == "add") {
            Add add;
            add.listing();
        } else {
            cout << "Wrong Typing\n";
        }
    }

    return 0;
}
