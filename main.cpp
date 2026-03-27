#include <SFML/Graphics.hpp>
#include "grille.hpp"
#include <cmath>
#include <vector>
#include "start.hpp"
#include "fantome.hpp"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <ctime>


void gererEvenements (sf::RenderWindow& window) {
    while (auto event = window.pollEvent()) { // On récupère les touches du claviers 
        if (event->is<sf::Event::Closed>()) {   // Si la croix est cliquée, on ferme la fenêtre
            window.close();
        }
    }
}

void updateScore (int& score, int tileSize, Grille& grille, const sf::Sprite& pacman, sf::Text& scoreText){
    int X = (pacman.getPosition().x) / tileSize; // calculer la position du pacman en fonction
    int Y = (pacman.getPosition().y) / tileSize;
    score += grille.point(X, Y);
    scoreText.setString("score " + std::to_string(score) + " points");
}

void dessiner(sf::RenderWindow& window,Grille& grille,sf::Sprite& pacman,std::vector<Fantome>& fantomes,sf::Text& scoreText)
{
    window.clear();
    grille.draw(window);
    window.draw(pacman);

    
    for (auto& f : fantomes)
    f.draw(window);
    

    window.draw(scoreText);
    window.display();
}

void gererInputPacman (sf::Vector2f& directionDemandee, float speed){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        directionDemandee = {-speed, 0.f};
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        directionDemandee = {speed, 0.f};
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        directionDemandee = {0.f, -speed};
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        directionDemandee = {0.f, speed};
    }
}
float distance(sf::Vector2f a, sf::Vector2f b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);


}





void updatePacman(sf::Sprite& pacman,Grille& grille,sf::Vector2f& directionActuelle,const sf::Vector2f& directionDemandee,int tileSize,float rayonPacman,float dt){
    sf::Vector2f center = pacman.getPosition();
    int currentCellX = (int)(center.x / tileSize); // cellule actuelle 
    int currentCellY = (int)(center.y / tileSize);

    float centerX = currentCellX * tileSize + tileSize / 2.f; // centre de la cel 
    float centerY = currentCellY * tileSize + tileSize / 2.f;

    float tolerance = 2.f; // tolérance pour tourner (pas pil poil)

    bool aligneX = std::abs(center.x - centerX) <= tolerance; //verifie si pacman est bien aligné
    bool aligneY = std::abs(center.y - centerY) <= tolerance;

    bool memeAxe = // regarde si en cliquant on reste sur le meme axe
        (directionActuelle.x != 0 && directionDemandee.x != 0) ||
        (directionActuelle.y != 0 && directionDemandee.y != 0);

    bool changementAxe = // regarde si on change d'axe
        (directionActuelle.x != 0 && directionDemandee.y != 0) ||
        (directionActuelle.y != 0 && directionDemandee.x != 0);

    int demandCellX = currentCellX; // la cellule demandé devient la cellule courante
    int demandCellY = currentCellY;// la cellule demandé devient la cellule courante

    if (directionDemandee.x > 0) demandCellX += 1; //on calcule la case voisine demandé
    else if (directionDemandee.x < 0) demandCellX -= 1;
    else if (directionDemandee.y > 0) demandCellY += 1;
    else if (directionDemandee.y < 0) demandCellY -= 1;

    bool demandeBloquee = grille.isWall(demandCellX, demandCellY, false); // regarde si case demandé est un mur

    bool peutTourner = false; 

    if (memeAxe) {
        peutTourner = true; // on garde l'alignement
    }
    else if (directionDemandee.x != 0) {
        peutTourner = aligneY; // on doit aligner sur y 
    }
    else if (directionDemandee.y != 0) {
        peutTourner = aligneX; // on doit aligner sur x
    }

    if (!demandeBloquee && peutTourner) { // si on peut tourner
        if (changementAxe) {
            pacman.setPosition({centerX, centerY}); // on tourne et on le met vrmt au centre
        }
        directionActuelle = directionDemandee; // la direction réele devient celle demandé
    }

    if (directionActuelle.x != 0) {
        pacman.setPosition({pacman.getPosition().x, centerY}); // forcer le pacman à rester dans le centre de la case 
    }
    else if (directionActuelle.y != 0) {
        pacman.setPosition({centerX, pacman.getPosition().y}); // idem ci-dessus
    }

    // tunnel de gauche à droite
    float droiteX = grille.cols() * tileSize; // la dernière colonne de droite (vide)
    float gaucheX = 0.f; // la première colonne de gauche (vide)
    if (pacman.getPosition().x < gaucheX) {
        pacman.setPosition({droiteX, pacman.getPosition().y});
    }
    else if (pacman.getPosition().x > droiteX) {
        pacman.setPosition({gaucheX, pacman.getPosition().y});
    }

    center = pacman.getPosition(); // on a change sa postion donc on recalule le centre pour bien aligné

    sf::Vector2f mouvement = directionActuelle * dt; // calcul du mouvmeent de la framer 
    sf::Vector2f nextPos = pacman.getPosition() + mouvement; // nextpos = poition futur coin haut gauche si on accpete 

    sf::Vector2f nextCenter = nextPos; // futur centre 

    sf::Vector2f testPoint = nextCenter; // point de collision 
    float margeMur = 3.f;

    if (directionActuelle.x > 0) { // un testpoint pour voir si on touch eun bord change en focntion de la direction du pac man
        testPoint.x += rayonPacman + margeMur;
        pacman.setRotation(sf::degrees(0));   // Pacman regarde à gauche
        
    }
    else if (directionActuelle.x < 0) {
        testPoint.x -= rayonPacman + margeMur;
        pacman.setRotation(sf::degrees(180));     // Pacman regarde à droite
        

    }
    else if (directionActuelle.y > 0) {
        testPoint.y += rayonPacman + margeMur;
        pacman.setRotation(sf::degrees(90));
    }
    else if (directionActuelle.y < 0) {
        testPoint.y -= rayonPacman + margeMur;
        pacman.setRotation(sf::degrees(270));
    }

    int cellX = (int)(testPoint.x / tileSize); // convertir le point en case 
    int cellY = (int)(testPoint.y / tileSize);

    bool bloque = grille.isWall(cellX, cellY, false); //collision mur 

    if (!bloque) {
        pacman.move(mouvement); // on avance qye si la route est libre 
    }
}



int main() {

    

    // ########################################################### Grille ###########################################################

    // taille du carre
    const int tileSize = 32;

    // création de la grille
    Grille grille(tileSize);

    //Cr&ation de la fenêtre
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(grille.cols()*tileSize, grille.rows() * tileSize+tileSize*2)), "Pacman");
    if (!showStartScreen(window)) {
        return 0;
    }

    // affichage du texte du score
    sf::Font font2;
    if (!font2.openFromFile("assets/PressStart2P-Regular.ttf")) {
        return -1; // erreur si la police ne charge pas
    }

    sf::Text scoreText(font2, "score ", 20);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition({30.f, 5.f});



    // ########################################################### FIN Grille ###########################################################

    // ########################################################### FANTOME ###########################################################


    // ########################################################### PACMAN ###########################################################



    int startX = 1; // case x de depart
    int startY = 1; // case y de depart

    
    std::vector<sf::Texture> pacmanTextures(5);
    float rayonPacman = tileSize * 0.4f;
    if (!pacmanTextures[0].loadFromFile("assets/1.png")) return -1;
    if (!pacmanTextures[1].loadFromFile("assets/2.png")) return -1;
    if (!pacmanTextures[2].loadFromFile("assets/3.png")) return -1;
    if (!pacmanTextures[3].loadFromFile("assets/4.png")) return -1;
    if (!pacmanTextures[4].loadFromFile("assets/5.png")) return -1;


    // création des fantomes 
    
    std::vector<Fantome> fantomes = {
        Fantome(sf::Color::Red,              {14 * tileSize+ tileSize/2.f, 11 * tileSize+ tileSize/2.f}, 100.f, 0.f),
        Fantome(sf::Color(255, 182, 255),    {13 * tileSize+ tileSize/2.f, 11 * tileSize+ tileSize/2.f}, 100.f, 3.f),
        Fantome(sf::Color::Cyan,             {14 * tileSize+ tileSize/2.f, 12 * tileSize+ tileSize/2.f}, 100.f, 6.f),
        Fantome(sf::Color(255, 165, 0),      {13 * tileSize+ tileSize/2.f, 12 * tileSize+ tileSize/2.f}, 100.f, 9.f)
    };
    
  
    // position du pacman au départ
    sf::Sprite pacman(pacmanTextures[0]);

    pacman.setOrigin({
        pacman.getTexture().getSize().x / 2.f,
        pacman.getTexture().getSize().y / 2.f
    });

    // 2. SCALE
    float scale = (tileSize * 0.8f) / pacman.getTexture().getSize().x;
    pacman.setScale({scale, scale});

    // 3. POSITION (APRÈS origin + scale)
    pacman.setPosition({
        startX * tileSize + tileSize / 2.f,
        startY * tileSize + tileSize / 2.f
    });

    float speed = 90.f; // gérer la vitesse de déplacement de Pacman 
    sf::Vector2f directionActuelle = {0.f, 0.f};
    sf::Vector2f directionDemandee = {0.f, 0.f};

    // ########################################################### FIN PACMAN ###########################################################
     
    


    // Horloge pour mésurer le temps entre chaque frame 
    sf::Clock clock;
    sf::Clock animationClock;
    int frame = 0;
    float animationSpeed = 0.12f;

    // aléatoire 
    std::srand(std::time(nullptr));
    int score = 0;

    sf::Clock ghostClock;
    int fantomesActifs = 1;
    float delai = 4.f;

    while (window.isOpen()) {
        // ########################################################### CLAVIER ###########################################################
        gererEvenements(window);

        float dt = clock.restart().asSeconds(); // Le temps depuis la dernière frame 
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            frame = (frame + 1) % 5;
            pacman.setTexture(pacmanTextures[frame], true); // true = reset rect

            pacman.setOrigin({
                pacman.getTexture().getSize().x / 2.f,
                pacman.getTexture().getSize().y / 2.f
            });
            animationClock.restart();
        }
        // On change de direction quand une touche est cliquée : les flêches ou ZQSD
        gererInputPacman(directionDemandee, speed);

        // ########################################################### FIN CLAVIER ###########################################################

       
        
        
        for (auto& f : fantomes)
            f.update(dt, pacman.getPosition(), tileSize, grille, pacman);
       
        updatePacman(pacman, grille, directionActuelle, directionDemandee, tileSize, rayonPacman, dt);

       // Si le Pacman mange un point, on change la couleur du point pour ne plus l'afficher
        updateScore(score,tileSize, grille,pacman,scoreText);
        // Etape pour ce qui s'affiche dans la fenêtre

        dessiner(window, grille, pacman, fantomes, scoreText);
    }

    return 0;
}