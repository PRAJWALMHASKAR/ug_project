#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>


using namespace std;
using namespace sf;


//Init game const
const double SCREEN_WIDTH = 800.0;
const double SCREEN_HEIGHT = 600.0;
//Road Border
const int borderLeft = 145;
const int borderRight = 655;
const int racerHeight = 70;     //racer.getsize().y;
string stringscore = "";
int score = 0;
double gameSpeed = 3.0;
double racerspeed = 2.0;


//Create Main Windows
RenderWindow app(VideoMode((int)(SCREEN_WIDTH), (int)(SCREEN_HEIGHT)), "!! Car Racing !!", Style::Default);

//Creat random Number for game loop
int getRandomNumber(int a, int b);

// Create gameover screen
int gameOver();



int getRandomNumber(int a, int b)
{
    static bool first = true;

    if (first)          // if(first != false)
    {
        srand((unsigned int)time(NULL));      // reset rand. no.
        first = false;
    }

    int result = a + rand() % ((b + 1) - a - 45);        //  a % 5 == ( 0 to 4 )
    //result = (result / 10) * 10;
    return result;
}


int main()
{
    //Setframerate limit
    app.setFramerateLimit(60);

    //Framerate independent => dt=0.16
    sf::Clock clock;
    float dt = 0.f;
    float mul = 62.5f;

    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    SoundBuffer acceleration;
    acceleration.loadFromFile("sound/Car interior.wav");
    Sound accel;
    accel.setBuffer(acceleration);

    //Init font
    Font myfont;
    myfont.loadFromFile("font/xirod.ttf");

    //Init texture
    Texture background, racer, obs1, obs2, obs3, obs4, gameover;

    //Load all images
    if (!background.loadFromFile("cars/background.png")) return EXIT_FAILURE;           //background size (840, 650)
    if (!racer.loadFromFile("cars/racer.png")) return EXIT_FAILURE;
    if (!obs1.loadFromFile("cars/obs1.png")) return EXIT_FAILURE;
    if (!obs2.loadFromFile("cars/obs2.png")) return EXIT_FAILURE;
    if (!obs3.loadFromFile("cars/obs3.png")) return EXIT_FAILURE;
    if (!obs4.loadFromFile("cars/obs4.png")) return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background), Background1(background), Racer(racer), Obs1(obs1), Obs2(obs2), Obs3(obs3), Obs4(obs4), Gameover(gameover);

    //Init co-ordinates
    double RacerX, RacerY, Obs1X, Obs1Y, Obs2X, Obs2Y, Obs3X, Obs3Y, Obs4X, Obs4Y;

    //Init racer and enemy position
    RacerX = SCREEN_WIDTH / 2;
    RacerY = SCREEN_HEIGHT - racer.getSize().y * 1.2;
    Obs1X = getRandomNumber(borderLeft, borderRight);
    Obs2X = getRandomNumber(borderLeft, borderRight);
    Obs3X = getRandomNumber(borderLeft, borderRight);
    Obs4X = getRandomNumber(borderLeft, borderRight);
    Obs1Y = 0.0;
    Obs2Y = -100.0;
    Obs3Y = -200.0;
    Obs4Y = -300.0;
    double BackgroundY1 = 0.0;
    double BackgroundY2 = -600.0;

    //Init racer position
    Racer.setPosition((float)RacerX, (float)RacerY);

    //Init enemy position
    Obs1.setPosition((float)Obs1X, (float)Obs1Y);
    Obs2.setPosition((float)Obs2X, (float)Obs2Y);
    Obs3.setPosition((float)Obs3X, (float)Obs3Y);
    Obs4.setPosition((float)Obs4X, (float)Obs4Y);

    //Audio
    GameSound.setVolume(10.f);
    GameSound.play();
    GameSound.setLoop(true);

    accel.setVolume(20.f);
    accel.play();
    accel.setLoop(true);


    //Update****************************************************************************

    //Game loop
    while (app.isOpen())
    {
        //Create event for input
        Event event;

        //Init and count score
        stringscore = "SCORE : " + to_string(score);
        //To update font use text class
        Text text(stringscore, myfont, 20);
        text.setPosition(5.f, 0.f);
        text.setFillColor(Color::White);

        //Dt is difference in fps
        dt = clock.restart().asSeconds();
        //std::cout << dt << "\n";

        //Update enemy position
        Obs1.setPosition((float)Obs1X, (float)Obs1Y);
        Obs2.setPosition((float)Obs2X, (float)Obs2Y);
        Obs3.setPosition((float)Obs3X, (float)Obs3Y);
        Obs4.setPosition((float)Obs4X, (float)Obs4Y);


        //Create scrolling background
        Background.setPosition(0, (float)BackgroundY1);
        Background1.setPosition(0, (float)BackgroundY2);
        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 600.0;
        }
        BackgroundY1 += 3.0 * dt * mul;
        BackgroundY2 += 3.0 * dt * mul;


        //Set Obs LOOP
        if (Obs1Y > SCREEN_HEIGHT)
        {
            Obs1X = getRandomNumber(borderLeft, borderRight);
            Obs1Y = -80.0;
            score++;
        }
        else
        {
            Obs1Y = Obs1Y + (gameSpeed + 0.5f) * (double)dt * (double)mul;
        }
        if (Obs2Y > SCREEN_HEIGHT)
        {
            Obs2X = getRandomNumber(borderLeft, borderRight);
            Obs2Y = -80.0;
            score++;
        }
        else
        {
            Obs2Y = Obs2Y + (gameSpeed + 0.5f) * (double)dt * (double)mul;
        }
        if (Obs3Y > SCREEN_HEIGHT)
        {
            Obs3X = getRandomNumber(borderLeft, borderRight);
            Obs3Y = -80.0;
            score++;
        }
        else
        {
            Obs3Y = Obs3Y + (gameSpeed + 0.5f) * (double)dt * (double)mul;
        }
        if (Obs4Y > SCREEN_HEIGHT)
        {
            Obs4X = getRandomNumber(borderLeft, borderRight);
            Obs4Y = -80.0;
            score++;
        }
        else
        {
            Obs4Y = Obs4Y + (gameSpeed + 0.5f) * (double)dt * (double)mul;
        }


        //Game level
        if (score > 25)
        {
            gameSpeed = 5.0 * (double)dt * (double)mul;
            
        }
        if (score > 50)
        {
            gameSpeed = 6.0 * (double)dt * (double)mul;

        }
        if (score > 100)
        {
            gameSpeed = 7.0 * (double)dt * (double)mul;
            

        }


        //Create event to handle input from keyboard
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        /*if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                if (RacerX > borderLeft) { RacerX = RacerX - 10; }
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                if (RacerX < borderRight) { RacerX = RacerX + 10; }
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                if (RacerY > 0) { RacerY = RacerY - 10; }
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                if (RacerY < SCREEN_HEIGHT - 70) { RacerY = RacerY + 10; }
            }
        }*/

        //Racer movement
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            Racer.move(0.f, -(float)racerspeed * dt * mul);
            BackgroundY1 += 1.5 * dt * mul;
            Obs1Y = Obs1Y + 1.5 * (double)dt * (double)mul;
            Obs2Y = Obs2Y + 1.5 * (double)dt * (double)mul;
            Obs3Y = Obs3Y + 1.5 * (double)dt * (double)mul;
            Obs4Y = Obs4Y + 1.5 * (double)dt * (double)mul;
            BackgroundY2 += 1.5 * dt * mul;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            Racer.move(0.f, (float)racerspeed * dt * mul);
            BackgroundY1 += -1.0 * dt * mul;
            Obs1Y = Obs1Y + -1.0 * (double)dt * (double)mul;
            Obs2Y = Obs2Y + -1.0 * (double)dt * (double)mul;
            Obs3Y = Obs3Y + -1.0 * (double)dt * (double)mul;
            Obs4Y = Obs4Y + -1.0 * (double)dt * (double)mul;
            BackgroundY2 += -1.0 * dt * mul;
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            Racer.move(-(float)racerspeed * dt * mul, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            Racer.move((float)racerspeed * dt * mul, 0.f);
        }

        //Racer collision with track-border
		if (Racer.getPosition().x <= borderLeft)		//Left
            Racer.setPosition(borderLeft, Racer.getPosition().y);
		if (Racer.getPosition().x >= borderRight - Racer.getGlobalBounds().width)	//Right
            Racer.setPosition(borderRight - Racer.getGlobalBounds().width, Racer.getPosition().y);
		if (Racer.getPosition().y <= 0.f)				//Top
            Racer.setPosition(Racer.getPosition().x, 0.f);
		if (Racer.getPosition().y >= app.getSize().y - Racer.getGlobalBounds().height)	//Bottom
            Racer.setPosition(Racer.getPosition().x, app.getSize().y - Racer.getGlobalBounds().height);



        //Collision between Racer and enemy
        /*if (((RacerX >= (Obs1X - 30)) && (RacerX <= (Obs1X + 30))) && ((RacerY >= (Obs1Y - 30)) && (RacerY) <= (Obs1Y + 30)))
        {
            GameSound.stop(); gameOver();
        };
        if (((RacerX >= (Obs2X - 30)) && (RacerX <= (Obs2X + 30))) && ((RacerY >= (Obs2Y - 30)) && (RacerY) <= (Obs2Y + 30)))
        {
            GameSound.stop(); gameOver();
        };
        if (((RacerX >= (Obs3X - 30)) && (RacerX <= (Obs3X + 30))) && ((RacerY >= (Obs3Y - 30)) && (RacerY) <= (Obs3Y + 30)))
        {
            GameSound.stop(); gameOver();
        };
        if (((RacerX >= (Obs4X - 30)) && (RacerX <= (Obs4X + 30))) && ((RacerY >= (Obs4Y - 30)) && (RacerY) <= (Obs4Y + 30)))
        {
            GameSound.stop(); gameOver();
        };*/
        if (Racer.getGlobalBounds().intersects(Obs1.getGlobalBounds())
            || Racer.getGlobalBounds().intersects(Obs2.getGlobalBounds())
            || Racer.getGlobalBounds().intersects(Obs3.getGlobalBounds())
            || Racer.getGlobalBounds().intersects(Obs4.getGlobalBounds()))
        {
            accel.stop();
            GameSound.stop();
            gameOver();
        }


        //Draw**********************************************************************

        //Clear and draw position
        app.clear();

        app.draw(Background);
        app.draw(Background1);
        app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text);
        
        app.display();
    }
    return EXIT_SUCCESS;    //return 0;
}



//int startGame()
//{
    //TODO
//}


//Game over
int gameOver()
{
    Texture gameover, troll;

    if (!gameover.loadFromFile("cars/Go1.png"))
        return EXIT_FAILURE;
    /*if (!troll.loadFromFile("cars/troll.png"))
        return EXIT_FAILURE;*/

    Sprite Gameover(gameover);
    //Sprite Troll(troll);

    //Troll.setPosition(90.f, 350.f);
    //Troll.scale(1.1f, 1.4f);
    
    SoundBuffer gameOver;
    gameOver.loadFromFile("sound/crash.wav");
    Sound GameOver;
    GameOver.setBuffer(gameOver);
    GameOver.setVolume(30.f);
    GameOver.play();

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        
        Font myfont;
        myfont.loadFromFile("font/xirod.ttf");

        //Troll.move(15.f, 7.f);
        
        stringscore = " YOUR SCORE :  " + to_string(score);
        Text text(stringscore, myfont, 30);
        text.setPosition(200.f, 100.f);
        text.setFillColor(Color::Yellow);
        
        app.clear();
        
        app.draw(Gameover);
        app.draw(text);
        //app.draw(Troll);
        
        app.display();

    }
    return 0;
}


