#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace ECS
{
struct Entity;
struct Filter;
class World;
} // namespace ECS

namespace Utilities
{

static class LogUtility
{
  public:
    enum class SortType
    {
        NONE,
        BY_RARITY,
        BY_PRICE_ASC,
        BY_PRICE_DESC
    };

  public:
    static std::string item_log_standart(std::shared_ptr<ECS::World> world, ECS::Entity &item_entity, int item_index);
    static void        print_items_table(std::shared_ptr<ECS::World>        world,
                                         const std::shared_ptr<ECS::Filter> itemsFilter,
                                         SortType                           sortType = SortType::NONE);

  public:
    static std::pair<int, int> GetConsoleSize()
    {
        int width  = 80;
        int height = 24;

#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        {
            width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
#else
        struct winsize size;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == 0)
        {
            width  = size.ws_col;
            height = size.ws_row;
        }
#endif

        return {width, height};
    }

    static std::vector<std::string> WrapText(const std::string &text, int maxWidth)
    {
        std::vector<std::string> lines;
        std::istringstream       wordsStream(text);
        std::string              word;

        std::string currentLine;

        while (wordsStream >> word)
        {
            // ≈сли добавление следующего слова превышает максимальную ширину
            if (currentLine.length() + word.length() + 1 > maxWidth)
            {
                if (!currentLine.empty())
                {
                    lines.push_back(currentLine);
                    currentLine.clear();
                }

                // ≈сли одно слово длиннее максимальной ширины, разбиваем его
                if (word.length() > maxWidth)
                {
                    while (word.length() > maxWidth)
                    {
                        lines.push_back(word.substr(0, maxWidth));
                        word = word.substr(maxWidth);
                    }
                    currentLine = word;
                }
                else
                {
                    currentLine = word;
                }
            }
            else
            {
                if (!currentLine.empty())
                {
                    currentLine += " ";
                }
                currentLine += word;
            }
        }

        if (!currentLine.empty())
        {
            lines.push_back(currentLine);
        }

        return lines;
    }

    static void ShowCenteredMessage(std::string &&message)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // ѕолучаем размеры консоли
        auto [consoleWidth, consoleHeight] = GetConsoleSize();

        // ћаксимальна€ ширина текста (оставл€ем отступы по бокам)
        int textMaxWidth = consoleWidth - 4;
        if (textMaxWidth < 20)
            textMaxWidth = 20; // ћинимальна€ ширина

        // ѕереносим текст
        auto wrappedLines = WrapText(message, textMaxWidth);

        // ¬ычисл€ем вертикальную позицию дл€ центрировани€
        int startRow = (consoleHeight - wrappedLines.size()) / 2;
        startRow     = max(1, startRow); // ћинимум перва€ строка

        // ѕеремещаем курсор и выводим сообщение
        for (int i = 0; i < startRow; ++i)
        {
            std::cout << "\n";
        }

        for (const auto &line : wrappedLines)
        {
            // ¬ычисл€ем отступ дл€ горизонтального центрировани€
            int padding = (consoleWidth - line.length()) / 2;
            padding     = max(0, padding);

            // ¬ыводим строку с отступами
            std::cout << std::string(padding, ' ') << line << "\n";
        }

        // ѕеремещаем курсор вниз
        std::cout << std::endl;
    }
};
} // namespace Utilities
