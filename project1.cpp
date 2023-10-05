#include <iostream>
using namespace std;
// using chaining for handling the collision

class MusicTrack
{
public:
    int ID;
    string title;
    string artist;
    string album;
    string genre;
    MusicTrack *next;

    MusicTrack()
    {
        ID = -1;
        title = "";
        artist = "";
        album = "";
        genre = "";
        next = NULL;
    }
    void getMusicTrack()
    {
        cout << "\nEnter ID : ";
        cin >> this->ID;
        cout << "\nEnter Title : ";
        cin >> this->title;
        cout << "\nEnter Artist : ";
        cin >> this->artist;
        cout << "\nEnter Album : ";
        cin >> this->album;
        cout << "\nEnter Genre : ";
        cin >> this->genre;
    }
    void putMusicTrack()
    {
        cout << "\nID     : " << this->ID;
        cout << "\nTitle  : " << this->title;
        cout << "\nArtist : " << this->artist;
        cout << "\nAlbum  : " << this->album;
        cout << "\nGenre  : " << this->genre;
    }
    void updateMusicTrack()
    {
        string title, artist, album, genre;
        cout << "\nPress Enter To Not Update";

        cout << "\nEnter Title  : ";
        cin >> title;
        if (title != "")
            this->title = title;

        cout << "\nEnter Artist : ";
        cin >> artist;
        if (artist != "")
            this->artist = artist;

        cout << "\nEnter Album : ";
        cin >> album;
        if (album != "")
            this->album = album;

        cout << "\nGenre : ";
        cin >> genre;
        if (genre != "")
            this->genre = genre;
    }
};

class MusicLibrary
{
public:
    MusicLibrary(int size);
    ~MusicLibrary();
    void AddTrack()
    {
        MusicTrack *temp = new MusicTrack();
        temp->getMusicTrack();
        int index = hash(temp->ID);

        if (table[index] == NULL)
        {
            table[index] = temp;
            cout << "\nAdded :" << table[index]->title << endl;
            return;
        }

        MusicTrack *current = table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = temp;
        cout << "\nAdded MUSIC :" << table[index]->title << endl;
        return;
    }
    void getTrack(int ID)
    {
        int index = hash(ID);
        MusicTrack *current = table[index];
        while (current != NULL)
        {
            if (current->ID == ID)
            {
                current->putMusicTrack();
                return;
            }
            current = current->next;
        }
        cout << "\nTRACK NOT FOUND!";
    }
    void deleteTrack(int ID)
    {
        int index = hash(ID);

        if (table[index] == NULL)
        {
            cout << "\nRecord Not Found !!";
            return;
        }
        MusicTrack *ptr = table[index], *prev;

        // deleting the first node
        if (table[index]->ID == ID)
        {
            if (ptr->next)
            {
                table[index] = ptr->next;
                return;
            }
            table[index] = NULL;
            return;
        }

        prev = ptr;
        ptr = ptr->next;
        while (ptr != NULL)
        {
            if (ptr->ID == ID)
            {
                if (ptr->next)
                {
                    prev->next = ptr->next;
                }
                else
                {
                    prev->next = NULL;
                }
                cout << "Deleted " << ptr->title;
                delete ptr;
            }
            prev = ptr;
            ptr = ptr->next;
        }
        cout << "\nRecord Not Found";
    }
    void updateTrack(int ID)
    {
        int index = hash(ID);
        MusicTrack *current = table[index];
        while (current != NULL)
        {
            if (current->ID == ID)
            {
                current->updateMusicTrack();
                return;
            }
            current = current->next;
        }
        cout << "\nTRACK NOT FOUND!";
    }
    bool searchSong(int id)
    {
        int index = hash(id);
        MusicTrack *current = table[index];
        while (current != NULL)
        {
            if (current->ID == id)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void displayIndex(int ID)
    {
        int index = hash(ID);
        MusicTrack *current = table[index];
        while (current != NULL)
        {
            if (current->ID == ID)
            {
                cout << current->ID << "\t" << current->title << endl;
                return;
            }
            current = current->next;
        }
    }

private:
    int hash(int key);
    int size;
    MusicTrack **table;
};

MusicLibrary::MusicLibrary(int size)
{
    this->size = size;
    table = new MusicTrack *[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = NULL;
    }
}

MusicLibrary::~MusicLibrary()
{
    for (int i = 0; i < size; i++)
    {
        MusicTrack *current = table[i];
        while (current != nullptr)
        {
            MusicTrack *next = current->next;
            delete current;
            current = next;
        }
    }
}

int MusicLibrary::hash(int key)
{
    return key % size;
}

class PlaylistTrack
{
public:
    int ID;
    PlaylistTrack *next;
    PlaylistTrack()
    {
        ID = -1;
        next = NULL;
    }
    PlaylistTrack(int ID)
    {
        this->ID = ID;
        next = NULL;
    }
};
class PlayList
{
public:
    PlaylistTrack *head;
    MusicLibrary *Library;

    PlayList(MusicLibrary *Library)
    {
        head = NULL;
        this->Library = Library;
    }
    void addToPlayList(int ID)
    {
        if (!Library->searchSong(ID))
        {
            cout << "\nTrack Not Found!!";
            return;
        }
        PlaylistTrack *temp = new PlaylistTrack(ID);
        PlaylistTrack *ptr = head;
        if (head == NULL)
        {

            head = temp;
            cout << "\nAdded " << endl;
            Library->displayIndex(ID);
            return;
        }
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
        cout << "\nAdded ";
        Library->displayIndex(ID);
    }
    void removeFromPlayList(int ID)
    {
        if (head == NULL)
        {
            cout << "\nNo Items" << endl;
            return;
        }
        if (head->ID == ID)
        {
            head = head->next;
            return;
        }

        PlaylistTrack *ptr, *prev;
        prev = head;
        ptr = head->next;
        while (ptr != NULL)
        {
            if (ptr->ID == ID)
            {
                prev->next = ptr->next;
                cout << "\nRemoved " << ptr->ID << " from Playlist";
                delete ptr;
                return;
            }
        }
        cout << "\nTrack Not Found!!";
    }
    void display()
    {
        PlaylistTrack *ptr = head;
        cout << "\nPlaylist" << endl;
        while (ptr != NULL)
        {
            Library->displayIndex(ptr->ID);
            ptr = ptr->next;
        }
    }
};

int main()
{
    int size, ch, id;

    cout << "\nEnter Size Of Hash Table : ";
    cin >> size;
    MusicLibrary *Library = new MusicLibrary(size);
    PlayList *myPlaylist = new PlayList(Library);

    do
    {
        cout << "\n*****************************************************"
             << "\n\t\tMUSIC LIBRARY SYSTEM"
             << "\n*****************************************************";
        cout << "\n\t\tMENU"
             << "\n\t1.Insert Track"
             << "\n\t2.Retrive Track"
             << "\n\t3.Update Track"
             << "\n\t4.Delete Track"
             << "\n\t5.Add To Playlist"
             << "\n\t6.Remove From Playlist"
             << "\n\t7.Display Playlist"
             << "\n\t8.Exit"
             << "\n\tEnter Your Choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            Library->AddTrack();
            break;
        case 2:
            cout << "\nEnter ID : ";
            cin >> id;
            Library->getTrack(id);
            break;
        case 3:
            cout << "\nEnter ID : ";
            cin >> id;
            Library->updateTrack(id);
            cout << "\nupdated";
            break;
        case 4:
            cout << "\nEnter ID : ";
            cin >> id;
            Library->deleteTrack(id);
            cout << "\nDeleted";
            break;
        case 5:
            cout << "\nEnter ID : ";
            cin >> id;
            myPlaylist->addToPlayList(id);
            break;
        case 6:
            cout << "\nEnter ID : ";
            cin >> id;
            myPlaylist->removeFromPlayList(id);
            cout << "\nRemoved from playlist";
            break;
        case 7:
            myPlaylist->display();
        default:
            break;
        }
    } while (ch != 8);
}