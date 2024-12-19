#include <iostream>
#include <cstdlib>
#include <cstdio> 
#include <string>
#include <cstring>
#include <unistd.h>

const char fileName[17] = "file.bin";

struct flights_t 
{
    int number;
    char type[30];
    char destination[30];
    char time[6];
};
typedef struct flights_t Flights;
Flights* flightsArr;

void input1() 
{
    FILE* workFile;
    workFile = fopen(fileName, "wb");

    if (!workFile)
    {
        std::cout << "Ошибка открытия";
        return;
    }

    int count;
    std::cout << "Введите количество рейсов: ";
    std::cin >> count;

    flightsArr = (Flights*) malloc (count * sizeof(Flights));
    for(int i = 0; i < count; ++i)
    {
        Flights flight;
        std::cout << "Введите номер рейса: ";
        std::cin >> flight.number;
        std::cout << "Введите тип самолета: ";
        std::cin >> flight.type;
        std::cout << "Введите пункт назначения: ";
        std::cin >> flight.destination;
        std::cout << "Введите время вылета (HH:MM): ";
        std::cin >> flight.time;
        flightsArr[i] = flight;
        std::cout << '\n';
    }

    fwrite(flightsArr, sizeof(Flights), count, workFile);
    fclose(workFile);
}

void input2()
{
    FILE* workFile;
    workFile = fopen(fileName, "wb");

    if (!workFile)
    {
        std::cout << "Ошибка открытия";
        return;
    }

    std::cout << "Выберите признак" << '\n'
                  << "1. Номер" << '\n' 
                  << "2. Тип" << '\n'
                  << "3. Пункт назначения" << '\n'
                  << "4. Время вылета" << '\n';
    int input;
    std::cin >> input;
    int numberStop;
    char typeStop[30];
    char destinationStop[30];
    char timeStop[6];

    switch (input)
    {
        case 1:
            std::cin >> numberStop;
            break;
        case 2:
            std::cin >> typeStop;
            break;
        case 3: 
            std::cin >> destinationStop;
            break;
        case 4: 
            std::cin >> timeStop;
            break;
    }

    int i = 0;
    flightsArr = (Flights*) malloc (1 * sizeof(Flights));

    while (1)
    {
        Flights flight;
        std::cout << "Введите номер рейса: ";
        std::cin >> flight.number;
        std::cout << "Введите тип самолета: ";
        std::cin >> flight.type;
        std::cout << "Введите пункт назначения: ";
        std::cin >> flight.destination;
        std::cout << "Введите время вылета (HH:MM): ";
        std::cin >> flight.time;
        flightsArr[i] = flight;

        bool f = 0;
        switch (input)
        {
            case 1:
            if(flightsArr[i].number == numberStop)
            f =1;
            break;
        case 2:
            if(flightsArr[i].type == typeStop)
            f =1;
            break;
        case 3: 
            if(flightsArr[i].destination == destinationStop)
            f =1;
            break;
        case 4: 
            if(flightsArr[i].time == timeStop)
            f =1;
            break;
        }

        i++;
        if(f) break;

        flightsArr = (Flights*) realloc(flightsArr, (i + 1) * sizeof(Flights));
    }

    fwrite(flightsArr, sizeof(Flights), i, workFile);
    fclose(workFile);
}

void input3()
{
    FILE* workFile;
    workFile = fopen(fileName, "wb");

    if (!workFile)
    {
        std::cout << "Ошибка открытия";
        return;
    }

    flightsArr = (Flights*) malloc (1 * sizeof(Flights));
    int i = 0;

    while (1)
    {
        std::cout << "Введите данные " << i + 1 << "-го рейса: ";

        Flights flight;
        std::cout << "Введите номер рейса: ";
        std::cin >> flight.number;
        std::cout << "Введите тип самолета: ";
        std::cin >> flight.type;
        std::cout << "Введите пункт назначения: ";
        std::cin >> flight.destination;
        std::cout << "Введите время вылета (HH:MM): ";
        std::cin >> flight.time;
        flightsArr[i] = flight;

        std::cout << "Введите 1, если хотите продолжить ввод и 2, если хотите прекратить: ";
        int check;
        std::cin >> check;
        bool f = 0;
        i++;

        switch (check)
        {
        case 1: 
            flightsArr = (Flights*) realloc(flightsArr, (i + 1) * sizeof(Flights));
            break;
        case 2:
            f = 1;
        default:
            break;
        }
         
        if (f)
            break;
    }
    

}

void inputSelection()
{
    std::cout << "Выберите тип ввода" << '\n'
              << "1. Заранее заданного количество структур" << '\n'
              << "2. До появления структуры с заданным признаком" << '\n'
              << "3. Ввод с диалогом" <<'\n';
    int selection;
    std::cin >> selection;
    switch (selection)
    {
        case 1:
            input1();
            break;
        case 2: 
            input2();
            break;
        case 3:
            input3();
            break;
    }
}

void viewFlights() 
{
    FILE* workFile = fopen(fileName, "rb");

    if (!workFile) {
        std::cout << "Ошибка открытия файла" << '\n';
        return;
    }

    std::cout << "Расписание рейсов:" << '\n';
    std::cout << "Номер рейса | Тип самолета | Пункт назначения | Время вылета" << '\n';

    Flights flight;
    int count = 0;
    while (fread(&flight, sizeof(Flights), 1, workFile) == 1) 
    {
        std::cout << flight.number << " | "
                  << flight.type << " | "
                  << flight.destination << " | "
                  << flight.time << '\n';
        count++;
    }
    std::cout << '\n';

    if (count == 0) 
    {
        std::cout << "Нет доступных рейсов." << '\n';
    }

    fclose(workFile);
}

void addFlightsToFile() 
{
    FILE* workFile;
    workFile = fopen(fileName, "ab");

    if (!workFile) 
    {
        std::cout << "Ошибка открытия" << std::endl;
        return;
    }

    int currentCount = 0;
    while (fread(&flightsArr[currentCount], sizeof(Flights), 1, workFile) == 1) 
    {
        currentCount++;
    }

    int newCount;
    std::cout << "Введите количество рейсов для добавления: ";
    std::cin >> newCount;
    std::cout << '\n';

    flightsArr = (Flights*) realloc(flightsArr, (currentCount + newCount) * sizeof(Flights));

    if (!flightsArr) 
    {
        std::cout << "Ошибка выделения памяти" << '\n';
        fclose(workFile);
        return;
    }

    for (int i = 0; i < newCount; ++i) 
    {
        Flights flight;
        std::cout << "Введите номер рейса: ";
        std::cin >> flight.number;
        std::cout << "Введите тип самолета: ";
        std::cin >> flight.type;
        std::cout << "Введите пункт назначения: ";
        std::cin >> flight.destination;
        std::cout << "Введите время вылета (HH:MM): ";
        std::cin >> flight.time;

        flightsArr[currentCount + i] = flight;
    }

    fseek(workFile, currentCount * sizeof(Flights), 0);
    fwrite(flightsArr + currentCount, sizeof(Flights), newCount, workFile);
    fclose(workFile);
}

void searchFlight()
{
    FILE* workFile = fopen(fileName, "rb");

    if (!workFile) 
    {
        std::cout << "Ошибка открытия файла." << '\n';
        return;
    }

    int count = 0;
    while (fread(&flightsArr[count], sizeof(Flights), 1, workFile) == 1) 
    {
        count++;
    }

    if (count == 0) 
    {
        std::cout << "Нет доступных рейсов для поиска" << '\n';
        fclose(workFile);
        return;
    }

    int choice;
    std::cout << '\n' << "Выберите параметр для поиска: " << '\n';
    std::cout << "1. Номер рейса" << '\n' 
              << "2. Тип самолета" << '\n'
              << "3. Пункт назначения" << '\n'
              << "4. Время вылета" << '\n';
    std::cin >> choice;

    switch(choice)
    {
        case 1:
        {
            int searchNumber;
            std::cout << "Введите номер рейса: " << '\n';
            std::cin >> searchNumber;
            bool found = false;

            for (int i = 0; i < count; ++i) 
            {
                if (flightsArr[i].number == searchNumber) 
                {
                    found = true;
                    std::cout << '\n' << "Номер рейса | Тип самолета | Пункт назначения | Время вылета" << '\n';
                    std::cout << flightsArr[i].number << " | "
                              << flightsArr[i].type << " | "
                              << flightsArr[i].destination << " | "
                              << flightsArr[i].time << '\n';
                }
            }
            if (!found)
                std::cout << "Рейс с номером " << searchNumber << " не найден." << '\n';
            break;
        }
        case 2:
        {
            char searchType[30];
            std::cout << "Введите тип самолета: " << '\n';
            std::cin >> searchType;
            bool found = false;

            for (int i = 0; i < count; ++i) 
            {
                if (strcmp(flightsArr[i].type, searchType) == 0)
                {
                    found = true;
                    std::cout << "Номер рейса | Тип самолета | Пункт назначения | Время вылета" << '\n';
                    std::cout << flightsArr[i].number << " | "
                              << flightsArr[i].type << " | "
                              << flightsArr[i].destination << " | "
                              << flightsArr[i].time << '\n';
                }
            }

            if (!found) 
                std::cout << "Рейсы с типом " << searchType << " не найдены." << '\n';
            break;
        }
        case 3:
        {
            char searchDestination[30];
            std::cout << "Введите пункт назначения: " << '\n';
            std::cin >> searchDestination;
            bool found = false;

            for (int i = 0; i < count; ++i) 
            {
                if (strcmp(flightsArr[i].destination, searchDestination) == 0) 
                {
                    found = true;
                    std::cout << "Номер рейса | Тип самолета | Пункт назначения | Время вылета" << '\n';
                    std::cout << flightsArr[i].number << " | "
                              << flightsArr[i].type << " | "
                              << flightsArr[i].destination << " | "
                              << flightsArr[i].time << '\n';
                }
            }

            if (!found) 
                std::cout << "Рейсы с пунктом назначения " << searchDestination << " не найдены." << '\n';
            break;
        }
        case 4:
        {
            char searchTime[6];
            std::cout << "Введите время вылета (HH:MM): " << '\n';
            std::cin >> searchTime;
            bool found = false;

            for (int i = 0; i < count; ++i) 
            {
                if (strcmp(flightsArr[i].time, searchTime) == 0) 
                {
                    found = true;
                    std::cout << "Номер рейса | Тип самолета | Пункт назначения | Время вылета" << '\n';
                    std::cout << flightsArr[i].number << " | "
                              << flightsArr[i].type << " | "
                              << flightsArr[i].destination << " | "
                              << flightsArr[i].time << '\n';
                }
            }

            if (!found) 
                std::cout << "Рейсы с временем вылета " << searchTime << " не найдены." << '\n';
            break;
        }
        default:
            std::cout << "Неверный выбор." << '\n';
            break;
    }

    fclose(workFile);
}

void deletionFlight()
{
    FILE* workFile = fopen(fileName, "r+b");

    if (!workFile) 
    {
        std::cout << "Ошибка открытия файла" << '\n';
        return;
    }

    int deleteNumber;
    std::cout << "Введите номер рейса для удаления" << '\n';
    std::cin >> deleteNumber;

    Flights flight;
    bool found = false;
    int position = 0;

    while (fread(&flight, sizeof(Flights), 1, workFile) == 1)
    {
        if (flight.number == deleteNumber) 
        {
            found = true;
            break;
        }
        position += sizeof(Flights);
    }

    if (!found) 
    {
        std::cout << "Рейс с номером " << deleteNumber << " не найден." << '\n';
        fclose(workFile);
        return;
    }

    Flights nextFlight;
    long nextPosition;

    while (fread(&nextFlight, sizeof(Flights), 1, workFile) == 1) 
    {
        nextPosition = ftell(workFile);
        fseek(workFile, position, 0);
        fwrite(&nextFlight, sizeof(Flights), 1, workFile);
        position = nextPosition;
    }

    ftruncate(fileno(workFile), position); 
    std::cout << "Рейс с номером " << deleteNumber << " удалён." << '\n';

    fclose(workFile);
}

void changeFlight()
{
    FILE* workFile = fopen(fileName, "r+b");

    if (!workFile) {
        std::cout << "Ошибка открытия файла" << '\n';
        return;
    }

    int changeNumber;
    std::cout << "Введите номер рейса, который хотите изменнить" << '\n';
    std::cin >> changeNumber;

    Flights flight;
    bool found = false;
    int position = 0;

    while (fread(&flight, sizeof(Flights), 1, workFile) == 1)
    {
        if (flight.number == changeNumber) 
        {
            found = true;
            break;
        }
        position += sizeof(Flights);
    }

     if (!found) 
    {
        std::cout << "Рейс с номером " << changeFlight << " не найден." << '\n';
        fclose(workFile);
        return;
    }

    std::cout << "Введите новый тип рейса: ";
    std::cin >> flight.type;
    std::cout << "Введите новое направление: ";
    std::cin >> flight.destination;
    std::cout << "Введите новое время: ";
    std::cin >> flight.time;

    fseek(workFile, position, 0);
    fwrite(&flight, sizeof(Flights), 1, workFile);
    fclose(workFile);
}

void quickSort(Flights* arr, int start, int end)
{
    if (start >= end) return;
    int x = arr[start + (end - start) / 2].number;

    int L = start, R = end;

    while (L <= R)  
    {
        while (arr[L].number < x)
            L++;
        while (arr[R].number > x)
            R--;

        if (L <= R)
        {
            std::swap(arr[L], arr[R]);
            L++;
            R--;
        }
    }

    if (start < R) quickSort(arr, start, R);
    if (L < end) quickSort(arr, L, end);

    return;
}

void sortingFlights ()
{
    FILE* workFile = fopen(fileName, "r+b");

    if (!workFile) {
        std::cout << "Ошибка открытия файла" << '\n';
        return;
    }

    int count = 0;
    while (fread(&flightsArr[count], sizeof(Flights), 1, workFile) == 1) 
    {
        count++;
    }

    if (count == 0) 
    {
        std::cout << "Нет доступных рейсов для сортировки" << '\n';
        fclose(workFile);
        return;
    }

    quickSort(flightsArr, 0, count - 1);

    std::cout << "Расписание рейсов:" << '\n';
    std::cout << "Номер рейса | Тип самолета | Пункт назначения | Время вылета" << '\n';

    for(int i = 0; i < count; ++i)
    {
        std::cout << flightsArr[i].number << " | "
                  << flightsArr[i].type << " | "
                  << flightsArr[i].destination << " | "
                  << flightsArr[i].time << '\n';
    }
    std::cout << '\n';

    fwrite(flightsArr, sizeof(Flights), count, workFile);
    fclose(workFile);
}

void menu()
{
    int choice;
    do
    {    
        std::cout << "Выберите, что вы хотите сделать" << '\n'
                  << "1. Ввод данных о рейсах" << '\n' 
                  << "2. Просмотр данных о рейсах" << '\n'
                  << "3. Добавить рейс" << '\n'
                  << "4. Поиск рейса" << '\n'
                  << "5. Удалить рейс" << '\n'
                  << "6. Изменить данные о рейсе" << '\n'
                  << "7. Сортировать по номеру" << '\n'
                  << "0. Выход" << '\n';
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                inputSelection();
                break;
            case 2:
                viewFlights();
                break;
            case 3:
                addFlightsToFile();
                break;
            case 4:
                searchFlight();
                break; 
            case 5:
                deletionFlight();
                break;
            case 6:
                changeFlight();
                break;
            case 7:
                sortingFlights ();
                break;
            default: 
                std::cout << '\n' << "Некорректный ввод" << "\n\n";
                break;
        }

    } while (choice != 0);
}

int main()
{
    menu();
    return 0;
}