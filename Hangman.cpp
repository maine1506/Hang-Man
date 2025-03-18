#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cctype>

using namespace std;

vector<string> loadFrames(const string& filename);
vector<string> loadWords(const string& filename);
string chooseWord(const vector<string>& wordList);
void update(const string& secretWord, char guess, string &guessedWord);
bool contains(char guess, const string& secretWord);
void render(string& guessedWord, int& badGuessCount, const vector<string>& frames, const string& wrongGuesses);
char readAGuess();

const int MAX_BAD_GUESSES = 7;

int main()
{
    srand(time(0));

    // Load dữ liệu từ file
    vector<string> frames = loadFrames("hangman_frames.txt");
    vector<string> wordList = loadWords("word_list.txt");

    // Chọn từ ngẫu nhiên
    string secretWord = chooseWord(wordList);
    int badGuessCount = 0;
    string guessedWord = string(secretWord.length(), '-');
    string wrongGuesses = "";

    do {
        render(guessedWord, badGuessCount, frames, wrongGuesses);
        char guess = readAGuess();
        cout << endl;
        if (contains(guess, secretWord)) {
            update(secretWord, guess, guessedWord);
        } else {
            badGuessCount++;
            wrongGuesses += guess;
            wrongGuesses += " ";
        }
    } while (badGuessCount < MAX_BAD_GUESSES && guessedWord != secretWord);

    render(guessedWord, badGuessCount, frames, wrongGuesses);
    if (guessedWord == secretWord)
        cout << "\nYOU WIN!!!\n";
    else
        cout << "\nYou lose. The answer is \"" << secretWord << "\".\n";

    return 0;
}

// Hàm đọc các khung treo cổ từ file
vector<string> loadFrames(const string& filename) {
    vector<string> frames;
    ifstream file(filename);
    if (!file) {
        cerr << "Không thể mở file " << filename << "!\n";
        exit(1);
    }
    string line, frame;
    while (getline(file, line)) {
        if (line.empty()) { // Khi gặp dòng trống, lưu frame
            frames.push_back(frame);
            frame.clear();
        } else {
            frame += line + "\n";
        }
    }
    if (!frame.empty()) frames.push_back(frame); // Lưu frame cuối cùng
    file.close();
    return frames;
}

// Hàm đọc danh sách từ vựng từ file
vector<string> loadWords(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    if (!file) {
        cerr << "Không thể mở file " << filename << "!\n";
        exit(1);
    }
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    return words;
}

// Chọn một từ ngẫu nhiên từ danh sách
string chooseWord(const vector<string>& wordList) {
    int randomIndex = rand() % wordList.size();
    return wordList[randomIndex];
}

// Kiểm tra ký tự có trong từ bí mật không
bool contains(char guess, const string& secretWord) {
    return (secretWord.find(guess) != string::npos);
}

// Cập nhật từ đã đoán với ký tự đúng
void update(const string& secretWord, char guess, string &guessedWord) {
    for (size_t i = 0; i < secretWord.length(); i++) {
        if (secretWord[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

// Hiển thị trạng thái hiện tại của trò chơi
void render(string& guessedWord, int& badGuessCount, const vector<string>& frames, const string& wrongGuesses) {
    system("CLS");
    for (int i = 0; i < 15; i++) cout << endl;

    cout << frames[badGuessCount] << endl;
    cout << "Word: " << guessedWord << endl;
    cout << "Wrong guesses: " << wrongGuesses << endl;
    cout << "Mistakes: " << badGuessCount << "/" << MAX_BAD_GUESSES << endl;

}

// Đọc ký tự đoán từ người chơi
char readAGuess() {
    char guess;
    cout << "Your guess: ";
    cin >> guess;
    return tolower(guess);
}
