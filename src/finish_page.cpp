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
    
    std::string titleText = isWon ? "Obrigado por Jogar!!!" : "Voce Morreu!";  
    std::string descriptionText = isWon ? "Pressione Espaco para sair" : "Pressione Espaco para tentar novamente";
    
    title.setString(titleText);
    title.setFillColor(isWon ? sf::Color::White : sf::Color::Red);
    title.setCharacterSize((int) (window->getSize().x * 0.08));
    title.setPosition((window->getSize().x / 2) - (title.getGlobalBounds().width / 2),30.0f);

    description.setString(descriptionText);
    description.setFillColor(sf::Color::White);  
    description.setCharacterSize((int) (window->getSize().x * 0.04));
    description.setPosition(
        (window->getSize().x / 2) - (description.getGlobalBounds().width / 2), 
        window->getSize().y - (description.getGlobalBounds().height + 50.0f)
    );
    isRendering = false;
}

bool FinishPage::verifyInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if(isWon) 
            window->close();
        else
            return true;
    }
    return false;
}

void FinishPage::render() {

        window->clear();
        window->draw(title);
        window->draw(description);
        window->display();

}