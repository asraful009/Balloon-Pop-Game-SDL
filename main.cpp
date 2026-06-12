
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "public/Window.h"
#include "public/Balloon.h"

static const std::string bn_digits[] = {"০", "১", "২", "৩", "৪", "৫", "৬", "৭", "৮", "৯"};

static const std::unordered_map<int, std::string> bn_weekdays = {
    {0, "রবিবার"}, {1, "সোমবার"}, {2, "মঙ্গলবার"}, {3, "বুধবার"}, {4, "বৃহস্পতিবার"}, {5, "শুক্রবার"}, {6, "শনিবার"}};

static const std::unordered_map<int, std::string> bn_months = {
    {0, "জানুয়ারী"}, {1, "ফেব্রুয়ারী"}, {2, "মার্চ"}, {3, "এপ্রিল"}, {4, "মে"}, {5, "জুন"}, {6, "জুলাই"}, {7, "আগস্ট"}, {8, "সেপ্টেম্বর"}, {9, "অক্টোবর"}, {10, "নভেম্বর"}, {11, "ডিসেম্বর"}};

// Helper to convert integer sequences safely to Bengali digits
std::string toBengaliNum(int number, int padding = 0)
{
    std::string engStr = std::to_string(number);
    std::string result = "";

    // Add leading zeros if requested padding is specified
    if (padding > 0 && engStr.length() < static_cast<size_t>(padding))
    {
        engStr = std::string(padding - engStr.length(), '0') + engStr;
    }

    for (char c : engStr)
    {
        if (c >= '0' && c <= '9')
        {
            result += bn_digits[c - '0'];
        }
        else
        {
            result += c;
        }
    }
    return result;
}

// Generate the complete Bengali time string natively from the system clock
std::string getBengaliTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *lt = std::localtime(&currentTime);

    // Get mapped values directly using tm integers safely
    std::string weekday = bn_weekdays.at(lt->tm_wday);
    std::string month = bn_months.at(lt->tm_mon);
    std::string year = toBengaliNum(lt->tm_year + 1900);
    std::string day = toBengaliNum(lt->tm_mday);

    // Calculate 12-hour format parameters
    int hour12 = lt->tm_hour % 12;
    if (hour12 == 0)
        hour12 = 12;
    std::string period = (lt->tm_hour >= 12) ? "অপরাহ্ণ" : "পূর্বাহ্ণ";

    std::string hour = toBengaliNum(hour12, 2);
    std::string minute = toBengaliNum(lt->tm_min, 2);
    std::string second = toBengaliNum(lt->tm_sec, 2);

    // Construct final layout string: "রবিবার মে ২০২৬, ২৪, ০৩:১৭:৪৭ অপরাহ্ণ"
    std::stringstream ss;
    ss << weekday << " " << month << " " << day << " " << year << ", "
       << hour << ":" << minute << ":" << second << " " << period;

    return ss.str();
}

int main()
{
    int w = 800, h = 640;
    int score = 0;
    Window *win = new Window("PopDrop.x86_64 V1.0", w, h);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = win->hexToRGBA(0x000000);
    long count = 0;
    long totalTime = 20;
    float timeAccumulator = 0.0f;

    std::vector<Balloon> balloons = {
        Balloon(100.0f, h - 20.0f, win),
        Balloon(200.0f, h - 30.0f, win),
        Balloon(300.0f, h - 40.0f, win),
        Balloon(400.0f, h - 10.0f, win),
        Balloon(500.0f, h - 15.0f, win),
        Balloon(600.0f, h - 05.0f, win),
    };
    bool previousLeft = false;
    float mx = .0f;
    float my = .0f;
    win->setUpdateCallback([&](float dt) {

        bool currentLeft = win->isMouseButtonDown(1);
        bool leftClicked = currentLeft && !previousLeft;
        previousLeft = currentLeft;
        mx = win->getMouseX();
        my = win->getMouseY();
        if (leftClicked) {      
            win->drawLine(mx - 10, my, mx + 10, my, {0, 255, 0, 255}); // horizontal
            win->drawLine(mx, my - 10, mx, my + 10, {0, 255, 0, 255}); // vertical      
            win->drawText("ক্লিক!", mx + 15, my - 15, {255, 0, 0, 255});
        }

        if (count >= totalTime) {
            win->drawText("সময় শেষ! আপনার স্কোর: " + toBengaliNum(score), (w / 2)-100, h / 2, red);
            if (leftClicked) {
                for (auto& balloon : balloons) {
                    balloon.reset();
                }
                count = 0;
                score = 0;

            }
            return; // Stop updating game logic after time is up
        }
        timeAccumulator += dt; // Smoothly adds up fractions of seconds
        if (timeAccumulator >= 1.0f) { // Every 1 whole second
            count++;
            timeAccumulator -= 1.0f; // Reset accumulator but keep leftovers
        }
        // std::string pos = "X: " + toBengaliNum(win->getMouseX()) + 
        //               "  Y: " + toBengaliNum(win->getMouseY());
        // win->drawText(pos, 50, 50, win->hexToRGBA(0x1B26FF));
        win->drawText("স্কোর: " + toBengaliNum(score) + " সময়: " + toBengaliNum(totalTime - count), 
            10.0, 10.0, win->hexToRGBA(0x2228FF));
        win->drawLine(10.0, 25.0, 200.0, 25.0, win->hexToRGBA(0x00ADB5));
        win->drawLine(10.0, 28.0, 200.0, 28.0, win->hexToRGBA(0x00ADB5)); 
        for (auto& balloon : balloons) {
            if (leftClicked) {
                balloon.isPop(mx, my, &score);
            }
            balloon.move(dt); 
            win->drawImage(balloon.getImage(), 
            static_cast<float>(balloon.getX()), 
            static_cast<float>(balloon.getY()));
        }
    });
    win->run();
    // for (auto& balloon : balloons) {
    //     delete balloon;
    // }
    delete win;
    return 0;
}