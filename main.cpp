#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct Song
{
    std::string title;
    std::string filePath;
    size_t year;
};

bool operator<(const Song& lhs, const Song& rhs)
{
    return lhs.year < rhs.year;
}

class DynamicPlaylist
{

public:
    void addToNextUp(const Song& song)
    {
        m_songs.push(song);
    }

    void switchNext()
    {
        m_songs.pop();
    }

    const Song& currentTrack() const
    {
        return m_songs.top(); // not front, but top()
    }

    auto size() /*-> decltype (m_songs)::size_type     - WOW! C++14 auto function return type deduction */
    {
        return m_songs.size();
    }

private:
    std::priority_queue<Song> m_songs;
};

std::vector<Song> scanFiles()
{
    std::vector<Song> data {
        {"Night Witches", "Sabaton/NightWitches.mp3", 2010},
        {"Resist and Bite", "Sabaton/ResistAndBite.mp3", 2012},
        {"Ghost Division", "Sabaton/GhostDivision.mp3", 2011},
        {"Primo Victoria", "Sabaton/PrimoVictoria.mp3", 2008}
    };
    std::string devicePath {"/run/media/sda1/"}; // flash drive mount point
    std::for_each(data.begin(), data.end(), [&](Song& song) {
        song.filePath.insert(0, devicePath);
    });

    return data;
}

DynamicPlaylist createPlaylist(const std::vector<Song>& data)
{
    DynamicPlaylist playlist;
    for (const auto& entry : data) {
        playlist.addToNextUp(entry);
    }
    return playlist;
}

void insestigateConstructors() {
    std::queue<std::string, std::vector<std::string>> test;
//    test.pop();

    std::deque<std::string> someData {"1", "2", "3"};
    std::queue<std::string> someQueue {someData}; // we can initialize with a copy of already created data

    auto comparator = [](const std::string& lhs, const std::string& rhs) {
            return lhs < rhs;
        };
    std::priority_queue<std::string, std::vector<std::string>, decltype (comparator)> somePriorityQueue {comparator};
}

int main()
{
    insestigateConstructors();

    const std::vector<Song>& scannedFiles {scanFiles()};

    DynamicPlaylist playlist {createPlaylist(scannedFiles)};

    std::cout << "Playlist created! It contains " << playlist.size() << " tracks. " << std::endl << std::endl;

    std::cout << "Now playing: ";
    std::cout << playlist.currentTrack().title << std::endl;

    std::cout << "Switching..." << std::endl;
    playlist.switchNext();

    std::cout << "Now playing: ";
    std::cout << playlist.currentTrack().title << std::endl;
    std::cout << std::endl << "Playlist size: " << playlist.size() << std::endl;

    return 0;
}
