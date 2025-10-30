#pragma once

#include "Components.h"
#include "DataBase.h"
#include "Filter.h"
#include "LogUtility.h"
#include "World.h"
#include <conio.h>
#include <string>

namespace Utilities
{

class ConsoleItemsAPI
{
  private:
    enum class Category
    {
        WEAPONS = 1,
        ARMOR,
        JEWELLERY,
        QUEST_ITEMS,
        ALL_ITEMS,
        EXIT = 0
    };

    enum class SortOption
    {
        NONE = 1,
        BY_RARITY,
        BY_PRICE_ASC,
        BY_PRICE_DESC,
        BACK = 0
    };

  public:
    static void ShowItems(std::shared_ptr<ECS::World> world)
    {
        if (!world)
        {
            std::cout << "Error: World is null!\n";
            return;
        }

        Category selectedCategory;

        do
        {
            ClearScreen();
            std::cout << "=== ITEM MANAGEMENT SYSTEM ===\n\n";

            ShowMenu();

            selectedCategory = GetCategoryChoice();

            if (selectedCategory != Category::EXIT)
            {
                ProcessCategorySelection(selectedCategory, world);
            }

        } while (selectedCategory != Category::EXIT);
    }

  private:
    static void ShowMenu()
    {
        std::cout << "Please select a category:\n";
        std::cout << "1. Weapons\n";
        std::cout << "2. Armor & Clothing\n";
        std::cout << "3. Jewellery\n";
        std::cout << "4. Quest Items\n";
        std::cout << "5. All Items\n";
        std::cout << "0. Exit\n\n";
        std::cout << "Enter your choice (0-5): ";
    }

    static void ShowSortMenu()
    {
        std::cout << "\n=== SORTING OPTIONS ===\n";
        std::cout << "1. No sorting (default)\n";
        std::cout << "2. Sort by rarity (highest first)\n";
        std::cout << "3. Sort by price (low to high)\n";
        std::cout << "4. Sort by price (high to low)\n";
        std::cout << "0. Back to categories\n\n";
        std::cout << "Enter your choice (0-4): ";
    }

    static Category GetCategoryChoice()
    {
        int choice;
        std::cin >> choice;

        while (std::cin.fail() || choice < 0 || choice > 5)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 0 and 5: ";
            std::cin >> choice;
        }

        std::cin.ignore(10000, '\n');
        return static_cast<Category>(choice);
    }

    static SortOption GetSortChoice()
    {
        int choice;
        std::cin >> choice;

        while (std::cin.fail() || choice < 0 || choice > 4)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 0 and 4: ";
            std::cin >> choice;
        }

        std::cin.ignore(10000, '\n');
        return static_cast<SortOption>(choice);
    }

    static SortOption AskForSorting()
    {
        ClearScreen();
        std::cout << "Would you like to sort the items?\n";
        std::cout << "1. Yes, show sorting options\n";
        std::cout << "2. No, display without sorting\n";
        std::cout << "0. Back to categories\n\n";
        std::cout << "Enter your choice (0-2): ";

        int choice;
        std::cin >> choice;

        while (std::cin.fail() || choice < 0 || choice > 2)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number between 0 and 2: ";
            std::cin >> choice;
        }

        std::cin.ignore(10000, '\n');

        if (choice == 0)
            return SortOption::BACK;
        if (choice == 2)
            return SortOption::NONE;

        // Если выбрали "Yes", показываем меню сортировки
        return ShowSortOptions();
    }

    static SortOption ShowSortOptions()
    {
        ClearScreen();
        ShowSortMenu();
        return GetSortChoice();
    }

    static void ProcessCategorySelection(Category category, std::shared_ptr<ECS::World> world)
    {
        // Спрашиваем пользователя о сортировке
        SortOption sortOption = AskForSorting();
        if (sortOption == SortOption::BACK)
            return;

        ClearScreen();

        // Преобразуем SortOption в SortType для LogUtility
        LogUtility::SortType sortType = ConvertSortOption(sortOption);

        switch (category)
        {
        case Category::WEAPONS:
            std::cout << "=== WEAPONS ===\n\n";
            ShowWeapons(world, sortType);
            break;

        case Category::ARMOR:
            std::cout << "=== ARMOR & CLOTHING ===\n\n";
            ShowArmor(world, sortType);
            break;

        case Category::JEWELLERY:
            std::cout << "=== JEWELLERY ===\n\n";
            ShowJewellery(world, sortType);
            break;

        case Category::QUEST_ITEMS:
            std::cout << "=== QUEST ITEMS ===\n\n";
            ShowQuestItems(world, sortType);
            break;
        case Category::ALL_ITEMS:
            std::cout << "=== ALL ITEMS ===\n\n";
            ShowAllItems(world, sortType);
            break;

        default:
            break;
        }

        std::cout << "\nPress any key to continue...";
        _getch();
    }

    static LogUtility::SortType ConvertSortOption(SortOption sortOption)
    {
        switch (sortOption)
        {
        case SortOption::BY_RARITY:
            return LogUtility::SortType::BY_RARITY;
        case SortOption::BY_PRICE_ASC:
            return LogUtility::SortType::BY_PRICE_ASC;
        case SortOption::BY_PRICE_DESC:
            return LogUtility::SortType::BY_PRICE_DESC;
        case SortOption::NONE:
        default:
            return LogUtility::SortType::NONE;
        }
    }

    static void ShowWeapons(std::shared_ptr<ECS::World> world,
                            LogUtility::SortType        sortType = LogUtility::SortType::NONE)
    {
        auto weaponsFilter = world->Filter()->With<Item>().With<Weapon>().Build();
        Utilities::LogUtility::print_items_table(world, weaponsFilter.lock(), sortType);
    }

    static void ShowArmor(std::shared_ptr<ECS::World> world, LogUtility::SortType sortType = LogUtility::SortType::NONE)
    {
        auto armorFilter = world->Filter()->With<Item>().With<Armor>().Build();
        Utilities::LogUtility::print_items_table(world, armorFilter.lock(), sortType);
    }

    static void ShowJewellery(std::shared_ptr<ECS::World> world, LogUtility::SortType sortType = LogUtility::SortType::NONE)
    {
        auto jewelleryFilter = world->Filter()->With<Item>().With<Jewellery>().Build();
        Utilities::LogUtility::print_items_table(world, jewelleryFilter.lock(), sortType);
    }

    static void ShowQuestItems(std::shared_ptr<ECS::World> world, LogUtility::SortType sortType = LogUtility::SortType::NONE)
    {
        auto questFilter = world->Filter()->With<Item>().With<QuestItem>().Build();
        Utilities::LogUtility::print_items_table(world, questFilter.lock(), sortType);
    }

    static void ShowAllItems(std::shared_ptr<ECS::World> world, LogUtility::SortType sortType = LogUtility::SortType::NONE)
    {
        auto itemsFilter = world->Filter()->With<Item>().Build();
        Utilities::LogUtility::print_items_table(world, itemsFilter.lock(), sortType);
    }

    static void ClearScreen()
    {
// Кроссплатформенная очистка экрана
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};

} // namespace Utilities