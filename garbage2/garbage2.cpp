
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

struct PlaylistSong
{
    string name;      // Название песни
    string author;    // Автор
    int releaseDate;  // Год выпуска
    int duration;     // Длительность (в секундах)
};

struct Playlist
{
    string name;   // Название плейлиста
    PlaylistSong* tracks;
    int size;     // Размер массива

    Playlist(int s) : size(s)
    {
        tracks = new PlaylistSong[size];
    }

    ~Playlist()
    {
        delete[] tracks;
    }
};
struct IndexNode  //создание узлов бинарного дерева 
{
    string key;
    int index;
    IndexNode* left;
    IndexNode* right;

    IndexNode(string k, int i) : key(k), index(i), left(nullptr), right(nullptr) {}
};

class IndexBinaryTree //бинарное дерево
{
private:
    IndexNode* root;

public:
    IndexBinaryTree() : root(nullptr) {}
    void outputBySongName(IndexNode* node, Playlist& playlist) //вывод по возрастанию имени песни
    {
        if (node == nullptr)
            return;
        outputBySongName(node->left, playlist);
        cout << "Название песни: " << playlist.tracks[node->index].name << endl;
        cout << "Исполнитель: " << playlist.tracks[node->index].author << endl;
        cout << "Год выпуска: " << playlist.tracks[node->index].releaseDate << endl;
        cout << "Длительность: " << playlist.tracks[node->index].duration << " секунд" << endl;
        cout << endl;
        outputBySongName(node->right, playlist);
    }
    void outputByReleaseDate(IndexNode* node, Playlist& playlist) //вывод по году выпуска
    {
        if (node == nullptr)
            return;
        outputByReleaseDate(node->right, playlist);
        cout << "Название песни: " << playlist.tracks[node->index].name << endl;
        cout << "Исполнитель: " << playlist.tracks[node->index].author << endl;
        cout << "Год выпуска: " << playlist.tracks[node->index].releaseDate << endl;
        cout << "Длительность: " << playlist.tracks[node->index].duration << " секунд" << endl;
        cout << endl;
        outputByReleaseDate(node->left, playlist);
    }
    void insertNode(string key, int index)
    {
        root = insertRec(root, key, index);
    }

    IndexNode* insertRec(IndexNode* root, string key, int index)
    {
        if (root == nullptr)
        {
            return new IndexNode(key, index);
        }
        if (key < root->key)
        {
            root->left = insertRec(root->left, key, index);
        }
        else if (key > root->key)
        {
            root->right = insertRec(root->right, key, index);
        }

        return root;
    }

    IndexNode* searchNode(string key)
    {
        return searchRec(root, key);
    }

    IndexNode* searchRec(IndexNode* root, string key)
    {
        if (root == nullptr || root->key == key)
        {
            return root;
        }
        if (key < root->key)
        {
            return searchRec(root->left, key);
        }
        return searchRec(root->right, key);
    }
};
void createIndexBySongName(IndexBinaryTree& tree, Playlist& playlist) //индекс по имени 
{
    for (int i = 0; i < playlist.size; i++)
    {
        tree.insertNode(playlist.tracks[i].name, i);
    }
}


void inputPlaylistTrack(PlaylistSong& track)   //Ввод данных
{
    cout << "Введите название песни: ";
    cin >> track.name;
    cout << "Введите исполнителя: ";
    cin >> track.author;
    while (true)
    {                                                               // Проверка ввода года выпуска
        cout << "Введите год выпуска: ";
        if (cin >> track.releaseDate && track.releaseDate >= 1900 && track.releaseDate <= 2024)
        {
            break;
        }
        else
        {
            cout << "Некорректный ввод. Введите число от 1900 до 2024 для года.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } // Проверка ввода года выпуска
    while (true)
    {                                                               // Проверка ввода длительности
        cout << "Введите длительность (в секундах): ";
        if (cin >> track.duration && track.duration >= 0)
        {
            break;
        }
        else
        {
            cout << "Некорректный ввод. Пожалуйста, введите неотрицательное целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }  // Проверка ввода длительности
};

void inputPlaylist(Playlist& playlist)      //Ввод данных для массива песен
{
    for (int i = 0; i < playlist.size; i++)
    {
        cout << "Введите данные для трека " << i + 1 << endl;
        inputPlaylistTrack(playlist.tracks[i]);
    }
}
void searchAndPrint(IndexBinaryTree& indexTree, const string& key, Playlist& playlist) //поиск элементов 
{
    IndexNode* foundNode = indexTree.searchNode(key);
    if (foundNode) {
        int index = foundNode->index;

        cout << "Название песни: " << playlist.tracks[index].name << endl;
        cout << "Исполнитель: " << playlist.tracks[index].author << endl;
        cout << "Год выпуска: " << playlist.tracks[index].releaseDate << endl;
        cout << "Длительность: " << playlist.tracks[index].duration << " секунд" << endl;
        cout << endl;
    }
    else {
        cout << "Элемент не найден." << endl;
    }
}
int Number(int n1, int n2)
{
    int number;
    do
    {
        cout << "Введите целое число от " << n1 << " до " << n2 << ": ";
        cin >> number;
        cout << endl;
        if (number < n1 || number > n2)
            cout << "Число вне диапазона! Попробуйте снова.\n";
        else
            break;

    } while (true);
    return number;
}


void printPlaylist(const Playlist& playlist)    //вывод массива
{
    for (int i = 0; i < playlist.size; ++i)
    {
        cout << "\nНазвание песни: " << playlist.tracks[i].name << endl;
        cout << "Исполнитель: " << playlist.tracks[i].author << endl;
        cout << "Год выпуска: " << playlist.tracks[i].releaseDate << endl;
        cout << "Длительность: " << playlist.tracks[i].duration << " секунд\n" << endl;
        cout << endl;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int number;
    do
    {
        cout << "1. Создать плейлист \n"
            << "2. Использовать готовый плейлист \n";
        number = Number(1, 3);
        switch (number)
        {
        case 1:  // Создать плейлист
        {
            int playlistSize;
            cout << "Введите размер плейлиста: ";
            while (!(cin >> playlistSize) || playlistSize <= 0)     //Ввод размера массива
            {
                cout << "Некорректный ввод. Пожалуйста, введите положительное целое число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            Playlist Playlist(playlistSize);   //Массив заданного размера 
            inputPlaylist(Playlist);
            do
            {
                cout << "1. Напечатать плейлист \n"
                    << "2. Напечатать плейлист в алфавитном порядке по названию песни \n"
                    << "3. Напечатать плейлист по убыванию года выпуска \n"
                    << "4. Поиск песни по имени \n";
                number = Number(1, 5);
                switch (number)
                {
                case 1: // Напечатать плейлист
                {
                    printPlaylist(Playlist);
                    break;
                }
                case 2: // Напечатать плейлист в алфавитном порядке по названию песни
                {
                    IndexBinaryTree indexTree;
                    createIndexBySongName(indexTree, Playlist);
                    indexTree.outputBySongName(indexTree.searchNode(Playlist.tracks[0].name), Playlist);
                    break;
                }
                case 3: // Напечатать плейлист по убыванию года выпуска
                {
                    IndexBinaryTree indexTree;
                    createIndexBySongName(indexTree, Playlist);
                    indexTree.outputByReleaseDate(indexTree.searchNode(Playlist.tracks[0].name), Playlist);
                    break;
                }
                case 4: // Поиск песни по имени 
                {
                    IndexBinaryTree indexTree;
                    createIndexBySongName(indexTree, Playlist);
                    string searchName;
                    cout << "Введите название песни для поиска '" << endl;
                    cin >> searchName;
                    cout << "Поиск песни с именем '" << searchName << "':" << endl;
                    searchAndPrint(indexTree, searchName, Playlist);
                    break;
                }
                case 5:
                {
                    break;
                }
                }
            } while (number < 6);
            break;
        }
        case 2: //Использовать готовый плейлист 
        {
            Playlist Playlist(3);
            Playlist.tracks[0].name = "Song4";
            Playlist.tracks[1].name = "Song1";
            Playlist.tracks[2].name = "Track89";
            Playlist.tracks[0].author = "Andrey";
            Playlist.tracks[1].author = "Autor1";
            Playlist.tracks[2].author = "Anon";
            Playlist.tracks[0].duration = 123;
            Playlist.tracks[1].duration = 232;
            Playlist.tracks[2].duration = 321;
            Playlist.tracks[0].releaseDate = 2012;
            Playlist.tracks[1].releaseDate = 2018;
            Playlist.tracks[2].releaseDate = 2012;
            do
            {
                cout << "1. Напечатать плейлист \n"
                    << "2. Напечатать плейлист в алфавитном порядке по названию песни \n"
                    << "3. Напечатать плейлист по убыванию года выпуска \n"
                    << "4. Поиск песни по имени \n";
                number = Number(1, 5);
                switch (number)
                {
                case 1: // Напечатать плейлист
                {
                    printPlaylist(Playlist);
                    break;
                }
                case 2: // Напечатать плейлист в алфавитном порядке по названию песни
                {
                    IndexBinaryTree indexTree;
                    createIndexBySongName(indexTree, Playlist);
                    indexTree.outputBySongName(indexTree.searchNode(Playlist.tracks[0].name), Playlist);
                    break;
                }
                case 3: // Напечатать плейлист по убыванию года выпуска
                {
                    IndexBinaryTree indexTree;
                    createIndexBySongName(indexTree, Playlist);
                    indexTree.outputByReleaseDate(indexTree.searchNode(Playlist.tracks[0].name), Playlist);
                    break;
                }
                case 4: // Поиск песни по имени 
                {
                    IndexBinaryTree indexTree;
                    createIndexBySongName(indexTree, Playlist);
                    string searchName;
                    cout << "Введите название песни для поиска '" << endl;
                    cin >> searchName;
                    cout << "Поиск песни с именем '" << searchName << "':" << endl;
                    searchAndPrint(indexTree, searchName, Playlist);
                    break;
                }
                case 5:
                {
                    number = 6;
                    break;
                }
                }
            } while (number < 6);
            break;
        }

        }
    } while (number < 4);



    return 0;
}

