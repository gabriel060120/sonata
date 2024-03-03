#include <string>
#include "finish_page.hpp"


FinishPage::FinishPage(sf::RenderWindow* window) {
    this->window = window;

    font.loadFromFile("../fonts/arial.ttf");
    title.setFont(font);
    description.setFont(font);
}

void FinishPage::init(bool isWon) {
    this->isWon = isWon;
    
    std::string titleText = isWon ? "Obrigado por Jogar!!!" : "Você Morreu!";  
    std::string descriptionText = isWon ? "Pressione Espaço para tentar novamente" : "Pressione Espaço para sair";
    
    title.setString(titleText);
    title.setFillColor(isWon ? sf::Color::Red : sf::Color::White);
    title.setCharacterSize((int) (window->getSize().x * 0.1));
    title.setPosition(0.0f,0.0f);

    description.setString(descriptionText);
    description.setFillColor(sf::Color::White);  
    isRendering = false;
}

bool FinishPage::verifyInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if(isWon) window->close();
        return true;
    }
    return false;
}

void FinishPage::render() {
    if(!isRendering) {
        isRendering = true;
        window->clear();
        window->draw(title);
        // window->draw(description);
        window->display();
    }
}