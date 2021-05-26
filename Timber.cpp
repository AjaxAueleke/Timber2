// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace sf;

const int BRANCHES = 100;
Sprite branch[BRANCHES];
bool branchpos[BRANCHES];
Texture branchleft, branchright;

int main()
{
    //VideoMode for my device [TODO : Have to make this for every screen resolution out there
    VideoMode vm(1280, 1024);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    Texture texturebackground;
    if (texturebackground.loadFromFile("graphics/Timberman_BG - Copy.jpg") == true)
    {
        std::cout << "Image Loaded Right" << std::endl;
    }
    else {
        std::cout << "This is shit" << std::endl;
    }

    Texture stem;
    stem.loadFromFile("graphics/stem.png");
    
    Sprite spriteStem[4];
    for (int i = 0; i < 4; i++)
    {
        spriteStem[i].setTexture(stem);
        spriteStem[i].setPosition(120, 0 + i * 100);
    }

    const int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().width;
    const int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().height;

    Texture plTexture;
    if (plTexture.loadFromFile("graphics/Timberman.png") == true)
    {
        std::cout << "Player texture loaded right" << std::endl;
    }
    else {
        std::cout << "Some error in loading the texture" << std::endl;
    }

    Sprite player;
    player.setTexture(plTexture);
    player.setPosition(300, 1140 / 2);
    player.scale(-0.5, 0.5);

    
    
    Texture tomb;
    tomb.loadFromFile("graphics/tomb.png");
    Sprite tombS;
    tombS.setTexture(tomb);
    Sprite moving_log;
    moving_log.setTexture(stem);
    moving_log.setPosition(120, 400);


    //
    Sprite spritebackground;

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    Clock clock;
    Time tchange;
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);

    double beeSpeed = 0;
    bool beeActive = false;
    spriteBee.setPosition(0, 400);


    spritebackground.setTexture(texturebackground);
    spritebackground.setPosition(0, 0);
    spriteTree.setPosition(120, 400);
    int score = 0;



    if (branchleft.loadFromFile("graphics/branch_left.png") == true)
    {
        std::cout << "branch Loaded Right" << std::endl;
    }
    else {
        std::cout << "branch error : not loaded right" << std::endl;

    }


    if (branchright.loadFromFile("graphics/branch_right.png") == true)
    {
        std::cout << "branch Loaded Right" << std::endl;
    }
    else {
        std::cout << "branch error : not loaded right" << std::endl;

    }


    srand((unsigned)time(0));
    for (int i = 0; i < BRANCHES; i++)
    {

        if (rand() % 2 == 0)
        {
            branch[i].setTexture(branchright);
            branchpos[i] = true;
        }
        else {
            branch[i].setTexture(branchleft);
            branchpos[i] = false;
        }
        branch[i].setScale(1, 0.25);

        int min = -1 * (branch[0].getTexture()->getSize().y * branch[0].getScale().y) * 350 ;

        branch[i].setPosition(120, (i * 300) + min);
        
    }

    
    Font font;
    if (!font.loadFromFile("font/static/Cinzel-SemiBold.ttf"))
    {
        std::cout << "font not correct" << std::endl;
    }
    else {
        std::cout << "font loaded right" << std::endl;
    }



    Text str_sc;
    str_sc.setFont(font);
    str_sc.setFillColor(Color::White);
    str_sc.setString("SCORE : 0");
    str_sc.setCharacterSize(50);
    str_sc.setPosition(20, 20);
    str_sc.setOrigin(1, 1);
    Text message;
    message.setFont(font);
    message.setString("PAUSED");
    message.setCharacterSize(100);
    message.setFillColor(Color::White);

    FloatRect textRect;
    textRect = message.getLocalBounds();
    message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    message.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    //Timebar
    RectangleShape timebar;
    timebar.setSize(Vector2f(300, 40));
    float width = 300;
    double persec = 60;
    bool paused = true; //flag (would be used for ui and menu later)


    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;


    std::string l; //score string


    bool recIn = false;



    Texture movingPlayer;
    movingPlayer.loadFromFile("graphics/t2.png");


    bool right = false;
    std::cout << "BRANCH    " <<branch[0].getTexture()->getSize().y * branch[0].getScale().y<<std::endl;
    while (window.isOpen())
    {
       // std::cout << "EVENT LOOP REACHED" << std::endl;
        l = "SCORE : "; //string for score message;
        l.append(std::to_string(score));
        str_sc.setString(l);

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;
            score = 0;
            width = 300;
            recIn = true;
        }

        if (right)  
        {
            int i = BRANCHES - 1;
            for (i = BRANCHES - 1; i > 0; i--)
            {
                if (branchpos[i] == true)
                {

                    if (branch[i].getPosition().y > player.getPosition().y && branch[i].getPosition().y < player.getPosition().y + (player.getTexture()->getSize().y * player.getScale().y))
                    {
                        std::cout << "COLLISION" << std::endl;
                        paused = true;
                        break;
                    }
                   
                }
            }
            
        }
        else
        {
            int i = BRANCHES - 1;
            for (i = BRANCHES - 1; i > 0; i--)
            {
                if (branchpos[i] == false)
                {
                    if (branch[i].getPosition().y > player.getPosition().y && branch[i].getPosition().y < player.getPosition().y + player.getTexture()->getSize().y * player.getScale().y)
                    {

                        std::cout << "COLLISION Player pos" << player.getPosition().y << "BRANCH " << branch[i].getPosition().y << std::endl;
                        paused = true;
                        break;
                    }
                    
                }
            }
            
            
        }
        

        if (recIn)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                player.setTexture(movingPlayer);
                player.setScale(-0.5, 0.5);
                player.setPosition(700, 1140 / 2);
                recIn = false;
                right = true;
                width = width + (60 * tchange.asSeconds());
                logSpeedX = -50000;
                logActive = true;
                for (int i = 0; i < BRANCHES; i++)
                {
                    if (branch[i].getPosition().y > player.getPosition().y && branch[i].getPosition().y < player.getPosition().y + (player.getTexture()->getSize().y * player.getScale().y))
                    {
                        branch[i].setPosition(120, branch[0].getPosition().y - 300);
                        score += 10;
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                player.setTexture(movingPlayer);
                player.setScale(0.5, 0.5);
                player.setPosition(300, 1140 / 2);
                recIn = false;
                for (int i = 0; i < BRANCHES; i++)
                {
                    if (branch[i].getPosition().y > player.getPosition().y && branch[i].getPosition().y < player.getPosition().y + (player.getTexture()->getSize().y * player.getScale().y))
                    {
                        branch[i].setPosition(120, branch[0].getPosition().y - 300);
                        score += 10;
                    }
                }
                right = false;
                width = width + (60 * tchange.asSeconds());
                logSpeedX = 500000;
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && !paused)
            {
                player.setTexture(plTexture);
                recIn = true;
            }
        }



        tchange = clock.restart();
        timebar.setSize(Vector2f(width, 40));
        timebar.setFillColor(Color::Red);
        timebar.setPosition((SCREEN_WIDTH / 2) - 200, 50);
        if (!paused)
        {
            if (!beeActive) {
                srand((int)time(0));
                beeSpeed = (rand() % 500) + 200;
                srand((int)time(0) * 10);
                double height = (rand() % 500);
                spriteBee.setPosition(1000, (float)height);
                beeActive = true;

            }

            else {
                if (spriteBee.getPosition().x < -200)
                {
                    beeActive = false;
                }
                spriteBee.setPosition(
                    (spriteBee.getPosition().x - (beeSpeed * 0.010)),
                    spriteBee.getPosition().y
                );
            }
            if (width > 0)
            {
                width = width - (6 * tchange.asSeconds());
            }
            else
            {
                width = 300;
            }
        }
  
        
        
        
     
        window.clear();
        window.draw(spritebackground);
        window.draw(spriteTree);



        for (int i = 0; i < 4; i++)
        {
            window.draw(spriteStem[i]);
        }
        
        window.draw(str_sc);
        window.draw(player);

        if (!paused)
        {
            for (int i = 0; i < BRANCHES; i++)
            {
                tchange = clock.restart();
                //std::cout << tchange.asSeconds() << " BeePos : " << spriteBee.getPosition().x << std::endl;

                branch[i].setPosition(120, branch[i].getPosition().y + 1 * 0.1 * (score + 1));
               // std::cout << "[BRANCH] Position X: " << branch[i].getPosition().x << "[BRANCH] Position Y : " << branch[i].getPosition().y << std::endl;
                //std::cout << "[BRANCH] Origin X : " << branch[i].getOrigin().x << "[BRANCH] Origin Y : " << branch[i].getOrigin().y << std::endl;
            }
        }
        for (int i = 0; i < BRANCHES; i++)
        {
            if (branch[i].getPosition().y > 800)
            {
                branch[i].setPosition(120, branch[0].getPosition().y - 300);
               
            }
            window.draw(branch[i]);

        }
        window.draw(moving_log);
        window.draw(timebar);
        /// <summary>
        /// The above function draws the entire scene.
        /// Some problem in font and animation but that can be solved easily.
        /// </summary>
        if (paused)
        {
            window.draw(message);
        }
        window.draw(spriteBee);

        window.display();

    }
        return 0;
    }
   
