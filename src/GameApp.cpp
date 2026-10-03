#include "GameApp.hpp"

#include <fstream>

namespace {
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const char* WINDOW_TITLE = "Canopy Tetris";
const float SKY_TOP = 34.0f;      // deep canopy green
const float SKY_BOTTOM = 96.0f;   // lighter green near the horizon
const float BAND_HEIGHT = 8.0f;

const char* FONT_CANDIDATES[] = {
    "assets/fonts/DejaVuSans.ttf",
    "assets/fonts/arial.ttf",
    "C:/Windows/Fonts/arial.ttf",
    "C:/Windows/Fonts/segoeui.ttf"
};
const int FONT_CANDIDATE_COUNT = 4;

bool fileExists(const char* path) {
    std::ifstream probe(path);
    return probe.good();
}

bool loadFont(sf::Font& font) {
    for (int i = 0; i < FONT_CANDIDATE_COUNT; i++) {
        if (fileExists(FONT_CANDIDATES[i]) && font.loadFromFile(FONT_CANDIDATES[i]))
            return true;
    }
    return false;
}
}

GameApp::GameApp()
    : window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
      clock_(),
      skyTop_(SKY_TOP),
      skyBottom_(SKY_BOTTOM) {
    window_.setFramerateLimit(60);
}

GameApp::~GameApp() {
}

void GameApp::run() {
    while (window_.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameApp::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

void GameApp::update() {
    // No gameplay yet: the well, the rope and the menu come in the next steps.
    (void)clock_;
}

void GameApp::render() {
    window_.clear(sf::Color(skyTop_, skyTop_, skyTop_));

    drawSky(window_);
    drawTitle(window_);

    window_.display();
}

void GameApp::drawSky(sf::RenderTarget& target) {
    // Vertical colour bands instead of a black void.
    unsigned int bandCount = static_cast<unsigned int>(WINDOW_HEIGHT / BAND_HEIGHT) + 1;
    for (unsigned int i = 0; i < bandCount; i++) {
        float t = static_cast<float>(i) / static_cast<float>(bandCount - 1);
        sf::Color band(skyTop_ + (skyBottom_ - skyTop_) * t,
                       120.0f + 60.0f * t,
                       skyTop_ + 20.0f);
        sf::RectangleShape strip(sf::Vector2f(WINDOW_WIDTH, BAND_HEIGHT));
        strip.setFillColor(band);
        strip.setPosition(0.0f, static_cast<float>(i) * BAND_HEIGHT);
        target.draw(strip);
    }
}

void GameApp::drawTitle(sf::RenderTarget& target) {
    sf::Font font;
    if (!loadFont(font))
        return;

    sf::Text title(WINDOW_TITLE, font, 54);
    title.setFillColor(sf::Color(250, 240, 200));
    sf::FloatRect box = title.getLocalBounds();
    title.setOrigin(box.width / 2.0f, 0.0f);
    title.setPosition(WINDOW_WIDTH / 2.0f, 60.0f);
    target.draw(title);

    sf::Text status("window + colored background ready", font, 22);
    status.setFillColor(sf::Color(230, 230, 230, 200));
    sf::FloatRect statusBox = status.getLocalBounds();
    status.setOrigin(statusBox.width / 2.0f, 0.0f);
    status.setPosition(WINDOW_WIDTH / 2.0f, 130.0f);
    target.draw(status);
}
