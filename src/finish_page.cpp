#include <string>
#include "finish_page.hpp"


FinishPage::FinishPage(sf::RenderWindow* window, bool isWon) {
    this->window = window;
    this->isWon = isWon;
    
    std::string titleText = isWon ? "Obrigado por Jogar!!!" : "Você Morreu!";  
    std::string descriptionText = isWon ? "Pressione Espaço para tentar novamente" : "Pressione Espaço para sair";  

    font.loadFromFile("../fonts/arial.ttf");
    title.setFont(font);
    description.setFont(font);

    title.setString(titleText);
    title.setFillColor(isWon ? sf::Color::Red : sf::Color::White);
    title.setCharacterSize((int) (window->getSize().x * 0.1));
    title.setPosition(0.0f,0.0f);

    description.setString(descriptionText);
    description.setFillColor(sf::Color::White);

}

bool FinishPage::verifyInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if(isWon) window->close();
        return true;
    }
    return false;
}

void FinishPage::render() {
    window->draw(title);
    // window->draw(description);
}