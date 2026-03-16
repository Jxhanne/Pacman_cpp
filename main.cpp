#include <SFML/Graphics.hpp>
#include "grille.hpp"
#include <cmath>
#include <vector>
#include "start.hpp"

int main() {

    // taille du carre
    const int tileSize = 32;
    int score = 0; // score du joueur

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




    int startX = 1; // case x de depart
    int startY = 1; // case y de depart

    
    std::vector<sf::Texture> pacmanTextures(5);

    if (!pacmanTextures[0].loadFromFile("assets/1.png")) return -1;
    if (!pacmanTextures[1].loadFromFile("assets/2.png")) return -1;
    if (!pacmanTextures[2].loadFromFile("assets/3.png")) return -1;
    if (!pacmanTextures[3].loadFromFile("assets/4.png")) return -1;
    if (!pacmanTextures[4].loadFromFile("assets/5.png")) return -1;

    sf::Sprite pacman(pacmanTextures[0]);

    // création des fantomes 
    sf::CircleShape fantome(tileSize * 0.4f);
    fantome.setFillColor(sf::Color::Red);

    pacman.setOrigin({
    pacman.getLocalBounds().size.x / 2.f,
    pacman.getLocalBounds().size.y / 2.f
    });
    float rayonPacman = tileSize * 0.4f; // rayon pacman
    float diametre = rayonPacman * 2.f;

    auto bounds = pacman.getLocalBounds().size;
    pacman.setScale({
        diametre / bounds.x,
        diametre / bounds.y
    });
    
    // position du pacman au départ
    pacman.setPosition({
        startX * tileSize + tileSize / 2.f,
        startY * tileSize + tileSize / 2.f
    });

    // position fantôme 
    int ghostStartX = 1;
    int ghostStartY = 4;

    float rayonFantome = fantome.getRadius();

    fantome.setPosition({
        ghostStartX * tileSize + tileSize / 2.f - rayonFantome,
        ghostStartY * tileSize + tileSize / 2.f - rayonFantome
    }); 

    // direction fantome
    sf::Vector2f directionFantome = {60.f, 0.f};

    float speed = 90.f; // gérer la vitesse de déplacement de Pacman 
    sf::Vector2f directionActuelle = {0.f, 0.f};
    sf::Vector2f directionDemandee = {0.f, 0.f};

    // Horloge pour mésurer le temps entre chaque frame 
    sf::Clock clock;
    sf::Clock animationClock;
    int frame = 0;
    float animationSpeed = 0.12f;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) { // On récupère les touches du claviers 
            if (event->is<sf::Event::Closed>())   // Si la croix est cliquée, on ferme la fenêtre
                window.close();
        }

        float dt = clock.restart().asSeconds(); // Le temps depuis la dernière frame 
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            frame = (frame + 1) % 5;
            pacman.setTexture(pacmanTextures[frame]);
            animationClock.restart();
        }
        // On change de direction quand une touche est cliquée : les flêches ou ZQSD
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

        // Avoir un mouvement fluide du Pacman 
        float rayon = rayonPacman; // obtenir le rayon du pacman

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

        bool demandeBloquee = grille.isWall(demandCellX, demandCellY); // regarde si case demandé est un mur

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
                pacman.setPosition({centerX, centerY});; // on tourne et on le met vrmt au centre
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
            testPoint.x += rayon + margeMur;
            pacman.setRotation(sf::degrees(0));   // Pacman regarde à gauche
            
        }
        else if (directionActuelle.x < 0) {
            testPoint.x -= rayon + margeMur;
            pacman.setRotation(sf::degrees(180));     // Pacman regarde à droite
            

        }
        else if (directionActuelle.y > 0) {
            testPoint.y += rayon + margeMur;
            pacman.setRotation(sf::degrees(90));
        }
        else if (directionActuelle.y < 0) {
            testPoint.y -= rayon + margeMur;
            pacman.setRotation(sf::degrees(270));
        }

        int cellX = (int)(testPoint.x / tileSize); // convertir le point en case 
        int cellY = (int)(testPoint.y / tileSize);

        bool bloque = grille.isWall(cellX, cellY); //collision mur 

        if (!bloque) {
            pacman.move(mouvement); // on avance qye si la route est libre 
        }

        //mouvement fantome
        float rayonFantome = fantome.getRadius(); // on obtient le rayon du cercle

        sf::Vector2f mouvementFantome = directionFantome * dt; // *dt pour qu'il aille à l amême vitesse tout le temps
        sf::Vector2f nextPosFantome = fantome.getPosition() + mouvementFantome; // on calcule la futurue position possible
        sf::Vector2f nextCenterFantome = nextPosFantome + sf::Vector2f(rayonFantome, rayonFantome); // et le futur centre 

        sf::Vector2f testPointFantome = nextCenterFantome; // on initialise le testpoint pour qu'il teste oû sont les murs

        if (directionFantome.x > 0) { // ces conditions déplace le testpoint pour qu'il soit placé au bon endroit "sur" le fantome
            testPointFantome.x += rayonFantome;
        }
        else if (directionFantome.x < 0) {
            testPointFantome.x -= rayonFantome;
        }
        else if (directionFantome.y > 0) {
            testPointFantome.y += rayonFantome;
        }
        else if (directionFantome.y < 0) {
            testPointFantome.y -= rayonFantome;
        }

        int ghostCellX = (int)(testPointFantome.x / tileSize); // la cellule du fantome x 
        int ghostCellY = (int)(testPointFantome.y / tileSize);

        bool ghostBlocked = grille.isWall(ghostCellX, ghostCellY); //on regarde is la cellule testé est un mur

        if (!ghostBlocked) { // si il n'est pas bloqué
            fantome.move(mouvementFantome); // onn le fait bouger
        }
        else {
            directionFantome = -directionFantome; // il va à l'inverse
        }

        // Si le Pacman mange un point, on change la couleur du point pour ne plus l'afficher
        int X = (pacman.getPosition().x) / tileSize; // calculer la position du pacman en fonction
        int Y = (pacman.getPosition().y) / tileSize;
        score += grille.point(X, Y);
        scoreText.setString("score " + std::to_string(score) + " points");

        // Etape pour ce qui s'affiche dans la fenêtre

        window.clear();
        grille.draw(window);
        window.draw(pacman);
        window.draw(fantome);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}