#include <iostream>
#include <ctime>

using namespace std;

string chooseWord();
void update(string secretWord, char guess, string &guessedWord);
bool contains(char guess, string secretWord);
void render(string guessedWord, int badGuessCount);
char readAGuess();
const int MAX_BAD_GUESSES = 7;


int main()
{
    srand(time(0));
    string secretWord = chooseWord();
    int badGuessCount = 0;
    string guessedWord = string(secretWord.length(), '-');

    do {
        render(guessedWord, badGuessCount);
        char guess = readAGuess();
        cout << endl;
        if (contains(guess, secretWord)) {
            update(secretWord, guess, guessedWord);
        }
        else badGuessCount++;
    } while (badGuessCount < MAX_BAD_GUESSES && guessedWord != secretWord);

    render(guessedWord, badGuessCount);
    if (guessedWord == secretWord) cout << "You win!";
    else cout << "You lose. The answer is \"" << secretWord << "\"." << endl;
    return 0;
}

void update(string secretWord, char guess, string &guessedWord) {
    int size = secretWord.length();
    for (int i = 0; i < size; i++) {
        if (guess == secretWord[i]) {
            guessedWord[i] = guess;
        }
    }
}

bool contains(char guess, string secretWord) {
    return (secretWord.find(guess) != string::npos);
}

char readAGuess() {
    char guess;
    cout << "Your guess: ";
    cin >> guess;
    return guess;
}

void render(string guessedWord, int badGuessCount) {
    cout << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
}

const string WORD_LIST[] = {
    "apple", "banana", "grape", "orange", "peach", "cherry", "melon", "berry", "lemon", "mango",
    "table", "chair", "sofa", "shelf", "lamp", "carpet", "pillow", "mirror", "curtain", "drawer",
    "ocean", "river", "mountain", "valley", "island", "desert", "waterfall", "glacier", "canyon", "forest",
    "happy", "sad", "angry", "excited", "nervous", "calm", "confused", "brave", "shy", "proud",
    "dog", "cat", "rabbit", "mouse", "tiger", "lion", "elephant", "giraffe", "dolphin", "penguin",
    "school", "teacher", "student", "classroom", "lesson", "subject", "homework", "library", "exam", "notebook",
    "computer", "laptop", "keyboard", "mouse", "screen", "printer", "software", "internet", "website", "server",
    "music", "guitar", "piano", "violin", "drum", "singer", "concert", "headphone", "melody", "orchestra",
    "car", "bus", "train", "bicycle", "motorcycle", "airplane", "ship", "submarine", "truck", "taxi",
    "doctor", "nurse", "hospital", "medicine", "patient", "surgery", "vaccine", "ambulance", "clinic", "treatment",
    "bread", "butter", "cheese", "milk", "yogurt", "honey", "coffee", "tea", "sugar", "salt",
    "morning", "afternoon", "evening", "midnight", "sunrise", "sunset", "weekend", "holiday", "birthday", "anniversary",
    "garden", "flower", "tree", "grass", "bush", "root", "leaf", "branch", "seed", "fruit",
    "phone", "message", "email", "letter", "postcard", "telegram", "call", "chat", "video", "contact",
    "king", "queen", "prince", "princess", "knight", "castle", "kingdom", "throne", "crown", "warrior",
    "friend", "family", "neighbor", "colleague", "partner", "teammate", "guest", "stranger", "childhood", "relative",
    "light", "dark", "shadow", "bright", "dim", "glow", "shine", "color", "rainbow", "reflection",
    "winter", "summer", "spring", "autumn", "snow", "rain", "wind", "storm", "fog", "thunder",
    "robot", "science", "experiment", "invention", "innovation", "discovery", "machine", "engine", "rocket", "satellite"
};
const int WORD_COUNT = sizeof(WORD_LIST) / sizeof(WORD_LIST[0]);
string chooseWord()
{
    int randomIndex = rand() % WORD_COUNT;
    return WORD_LIST[randomIndex];
}
