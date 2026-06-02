#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

enum Color { WHITE = 'W', GREEN = 'G', RED = 'R', BLUE = 'B', ORANGE = 'O', YELLOW = 'Y' };

void initializeCube(char cube[6][3][3]) 
{
    // Define the colors for each face
    char colors[6] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    // Fill each face with the corresponding color using double nested loops for a 3D array
    for (int f = 0; f < 6; ++f) 
    {
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                cube[f][i][j] = colors[f];
            }
        }
    }
}

// Function to rotate a face clockwise
void rotateFaceClockwise(char face[3][3]) 
{
    char temp[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            temp[j][2 - i] = face[i][j]; // logic for 90 degrees clockwise rotation
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            face[i][j] = temp[i][j];
}

// Function to rotate a face counterclockwise
void rotateFaceCounterClockwise(char face[3][3]) 
{
    char temp[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            temp[2 - j][i] = face[i][j]; // logic for 90 degrees anticlockwise rotation
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            face[i][j] = temp[i][j];
}// these functions just change the state of the face moved not the adjacent edges

// Function to rotate edges during a face rotation
void rotateEdges(char cube[6][3][3], int face, bool clockwise) 
{
    char temp[3];
    switch (face) {
        case 0: // WHITE (Top)
            if (clockwise) 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[4][0][i];
                for (int i = 0; i < 3; ++i) cube[4][0][i] = cube[1][0][i];
                for (int i = 0; i < 3; ++i) cube[1][0][i] = cube[2][0][i];
                for (int i = 0; i < 3; ++i) cube[2][0][i] = cube[3][0][i];
                for (int i = 0; i < 3; ++i) cube[3][0][i] = temp[i];
            } 
            else 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[4][0][i]; // ORANGE top row
                for (int i = 0; i < 3; ++i) cube[4][0][i] = cube[3][0][i]; // BLUE -> ORANGE
                for (int i = 0; i < 3; ++i) cube[3][0][i] = cube[2][0][i]; // RED -> BLUE
                for (int i = 0; i < 3; ++i) cube[2][0][i] = cube[1][0][i]; // GREEN -> RED
                for (int i = 0; i < 3; ++i) cube[1][0][i] = temp[i];      // ORANGE -> GREEN
            }
            break;

        case 1: // GREEN (Front)
            if (clockwise) 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][2][i]; // WHITE bottom row
                for (int i = 0; i < 3; ++i) cube[0][2][i] = cube[4][2 - i][2]; // ORANGE right col -> WHITE
                for (int i = 0; i < 3; ++i) cube[4][2 - i][2] = cube[5][0][2 - i]; // YELLOW top row -> ORANGE
                for (int i = 0; i < 3; ++i) cube[5][0][2 - i] = cube[2][i][0]; // RED left col -> YELLOW
                for (int i = 0; i < 3; ++i) cube[2][i][0] = temp[i];           // WHITE -> RED
            } 
            else 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][2][i];
                for (int i = 0; i < 3; ++i) cube[0][2][i] = cube[2][i][0];
                for (int i = 0; i < 3; ++i) cube[2][i][0] = cube[5][0][2 - i];
                for (int i = 0; i < 3; ++i) cube[5][0][2 - i] = cube[4][2 - i][2];
                for (int i = 0; i < 3; ++i) cube[4][2 - i][2] = temp[i];
            }
            break;

        case 2: // RED (Right)
            if (clockwise) 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][i][2]; // WHITE right col
                for (int i = 0; i < 3; ++i) cube[0][i][2] = cube[1][i][2]; // GREEN right col -> WHITE
                for (int i = 0; i < 3; ++i) cube[1][i][2] = cube[5][i][2]; // YELLOW right col -> GREEN
                for (int i = 0; i < 3; ++i) cube[5][i][2] = cube[3][2 - i][0]; // BLUE left col -> YELLOW
                for (int i = 0; i < 3; ++i) cube[3][2 - i][0] = temp[i];       // WHITE -> BLUE
            } 
            else 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][i][2];
                for (int i = 0; i < 3; ++i) cube[0][i][2] = cube[3][2 - i][0];
                for (int i = 0; i < 3; ++i) cube[3][2 - i][0] = cube[5][i][2];
                for (int i = 0; i < 3; ++i) cube[5][i][2] = cube[1][i][2];
                for (int i = 0; i < 3; ++i) cube[1][i][2] = temp[i];
            }
            break;

        case 3: // BLUE (Back)
            if (clockwise) 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][0][2 - i]; // WHITE top row reversed
                for (int i = 0; i < 3; ++i) cube[0][0][2 - i] = cube[2][i][2]; // RED right col -> WHITE
                for (int i = 0; i < 3; ++i) cube[2][i][2] = cube[5][2][i]; // YELLOW bottom row -> RED
                for (int i = 0; i < 3; ++i) cube[5][2][i] = cube[4][2 - i][0]; // ORANGE left col -> YELLOW
                for (int i = 0; i < 3; ++i) cube[4][2 - i][0] = temp[i];       // WHITE -> ORANGE
            } 
            else 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][0][2 - i];
                for (int i = 0; i < 3; ++i) cube[0][0][2 - i] = cube[4][2 - i][0];
                for (int i = 0; i < 3; ++i) cube[4][2 - i][0] = cube[5][2][i];
                for (int i = 0; i < 3; ++i) cube[5][2][i] = cube[2][i][2];
                for (int i = 0; i < 3; ++i) cube[2][i][2] = temp[i];
            }
            break;

        case 4: // ORANGE (Left)
            if (clockwise) 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][i][0]; // WHITE left col
                for (int i = 0; i < 3; ++i) cube[0][i][0] = cube[3][2 - i][2]; // BLUE right col -> WHITE
                for (int i = 0; i < 3; ++i) cube[3][2 - i][2] = cube[5][i][0]; // YELLOW left col -> BLUE
                for (int i = 0; i < 3; ++i) cube[5][i][0] = cube[1][i][0]; // GREEN left col -> YELLOW
                for (int i = 0; i < 3; ++i) cube[1][i][0] = temp[i];       // WHITE -> GREEN
            } 
            else 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[0][i][0];
                for (int i = 0; i < 3; ++i) cube[0][i][0] = cube[1][i][0];
                for (int i = 0; i < 3; ++i) cube[1][i][0] = cube[5][i][0];
                for (int i = 0; i < 3; ++i) cube[5][i][0] = cube[3][2 - i][2];
                for (int i = 0; i < 3; ++i) cube[3][2 - i][2] = temp[i];
            }
            break;

        case 5: // YELLOW (Bottom)
            if (clockwise) 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[1][2][i];
                for (int i = 0; i < 3; ++i) cube[1][2][i] = cube[4][2][i];
                for (int i = 0; i < 3; ++i) cube[4][2][i] = cube[3][2][i];
                for (int i = 0; i < 3; ++i) cube[3][2][i] = cube[2][2][i];
                for (int i = 0; i < 3; ++i) cube[2][2][i] = temp[i];
            } 
            else 
            {
                for (int i = 0; i < 3; ++i) temp[i] = cube[1][2][i]; // GREEN bottom row
                for (int i = 0; i < 3; ++i) cube[1][2][i] = cube[2][2][i]; // RED bottom row -> GREEN
                for (int i = 0; i < 3; ++i) cube[2][2][i] = cube[3][2][i]; // BLUE bottom row -> RED
                for (int i = 0; i < 3; ++i) cube[3][2][i] = cube[4][2][i]; // ORANGE bottom row -> BLUE
                for (int i = 0; i < 3; ++i) cube[4][2][i] = temp[i];       // GREEN -> ORANGE
            }
            break;


    //Separate cases for each color to ensure code functions perfectly.
    }
}

// Function to rotate a specific face
void rotateFace(char cube[6][3][3], int face, bool clockwise) 
{
    if (clockwise)
        rotateFaceClockwise(cube[face]);
    else
        rotateFaceCounterClockwise(cube[face]);
    rotateEdges(cube, face, clockwise); // calls function to first rotate the face and then move the corresponding edges in place.
}

void scrambleCube(char cube[6][3][3]) 
{
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 20; ++i) { // Perform 20 random moves
        int face = rand() % 6;
        bool clockwise = rand() % 2;
        rotateFace(cube, face, clockwise);
    }
    cout << "Cube scrambled.\n";
}

// Function to display the cube (for testing)
void displayCube(char cube[6][3][3]) 
{
    for (int f = 0; f < 6; ++f) {
        cout << "Face " << f << ":\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << cube[f][i][j] << " ";
            }
            cout << endl;
        }
    }
}

// Function to map cube colors to SFML colors
sf::Color mapColor(char color) 
{
    switch (color) 
    {
        case 'W': return sf::Color::White;
        case 'G': return sf::Color::Green;
        case 'R': return sf::Color::Red;
        case 'B': return sf::Color::Blue;
        case 'O': return sf::Color(255, 165, 0); // Orange
        case 'Y': return sf::Color::Yellow;
        default: return sf::Color::Black;
    }
}

// Function to render the Rubik's Cube using SFML
void renderCube(sf::RenderWindow& window, char cube[6][3][3]) 
{
    const int tileSize = 50;  // Size of each square
    const int padding = 10;  // Space between faces

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Moeed\\Desktop\\28100403_28100092\\coding\\Sansation_Bold_Italic.ttf")) 
    {
        cout << "Error loading font!" << endl;
        return;
    }


    // Create button texts
    sf::Text scrambleText("Press S to Scramble Cube", font, 18);
    scrambleText.setPosition(1000, 50);

    sf::Text resetText("Press Space to Reset Cube", font, 18);
    resetText.setPosition(1000, 100);

    sf::Text exitText("Press escape to Exit", font, 18);
    exitText.setPosition(1000, 150);

    vector<string> faceNames = {"White", "Yellow", "Green", "Orange", "Blue", "Red"};
    vector<char> faceKeys = {'W', 'Y', 'G', 'O', 'B', 'R'};

    vector<sf::Text> faceTexts;

    for (size_t i = 0; i < faceNames.size(); ++i) 
    {
        sf::Text text;
        text.setFont(font);
        text.setString("Press " + string(1, faceKeys[i]) + " to move " + faceNames[i] + " face clockwise or hold along L-shift to move anti-clockwise");
        text.setCharacterSize(18);
        text.setPosition(1000, 200 + static_cast<int>(i) * 50); // Adjust vertical spacing
        faceTexts.push_back(text);
    }

    // Face offsets for displaying each face on the window
    sf::Vector2f offsets[6] = 
    {
        {3 * tileSize + padding + 50, 0 + 50},                         // WHITE (Top)
        {3 * tileSize + padding + 50, 3 * tileSize + padding + 50},    // GREEN (Front)
        {6 * tileSize + 2 * padding + 50, 3 * tileSize + padding + 50}, // RED (Right)
        {9 * tileSize + 2 * padding + 60, 3 * tileSize + padding + 50},// BLUE (Back)
        {0 + 50, 3 * tileSize + padding + 50}, // ORANGE (Left)
        {3 * tileSize + padding + 50, 6 * tileSize + 2 * padding + 50}, // YELLOW (Bottom)

    };

    // Clear the window
    window.clear();

    // Draw each face of the cube
    for (int f = 0; f < 6; ++f) 
    {
        sf::Vector2f offset = offsets[f];
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(offset.x + j * tileSize, offset.y + i * tileSize);
                tile.setFillColor(mapColor(cube[f][i][j]));
                tile.setOutlineColor(sf::Color::Black);
                tile.setOutlineThickness(1);
                window.draw(tile);
            }
        }
    }

    window.draw(scrambleText);
    window.draw(resetText);
    window.draw(exitText);

    for (const auto& text : faceTexts) 
    {
        window.draw(text);
    }


    // Display the window
    window.display();
}

int main() 
{
    // Initialize the Rubik's Cube
    char cube[6][3][3];

    initializeCube(cube); 

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(1800, 1000), "Rubik's Cube Simulator");


    // Render the initial cube
    renderCube(window, cube);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key presses for rotation
            if (event.type == sf::Event::KeyPressed) 
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) 
                { // Check if Left Shift is pressed
                    switch (event.key.code) 
                    {
                        case sf::Keyboard::W:
                            rotateFace(cube, 0, false); // Rotate White anti-clockwise
                            break;
                        case sf::Keyboard::Y:
                            rotateFace(cube, 5, false); // Rotate YELLOW anti-clockwise
                            break;
                        case sf::Keyboard::G:
                            rotateFace(cube, 1, false); // Rotate GREEN anti-clockwise
                            break;
                        case sf::Keyboard::R:
                            rotateFace(cube, 2, false); // Rotate RED anti-clockwise
                            break;
                        case sf::Keyboard::B:
                            rotateFace(cube, 3, false); // Rotate BLUE anti-clockwise
                            break;
                        case sf::Keyboard::O:
                            rotateFace(cube, 4, false); // Rotate ORANGE anti-clockwise
                            break;
                        default:
                            break;
                    }
                } 
                else 
                {
                    // Handle regular key presses
                    switch (event.key.code) 
                    {
                    case sf::Keyboard::G:
                        rotateFace(cube, 1, true); // Rotate Green clockwise
                        break;
                    case sf::Keyboard::R:
                        rotateFace(cube, 2, true); // Rotate Green clockwise
                        break;
                    case sf::Keyboard::B:
                        rotateFace(cube, 3, true); // Rotate Red clockwise
                        break;
                    case sf::Keyboard::O:
                        rotateFace(cube, 4, true); // Rotate ORANGE clockwise
                        break;
                    case sf::Keyboard::W:
                        rotateFace(cube, 0, true); // Rotate WHITE clockwise
                        break;
                    case sf::Keyboard::Y:
                        rotateFace(cube, 5, true); // Rotate YELLOW clockwise
                        break;
                    case sf::Keyboard::Escape:
                        return 0;              //Exit Program
                    case sf::Keyboard::S:
                        scrambleCube(cube); // Scramble Cube
                        break;
                    case sf::Keyboard::Space:
                        initializeCube(cube); // Reset Cube
                        break;
                    default:
                        break;
                    }
                }
            


                // Re-render the cube after each rotation
                renderCube(window, cube);
            }
        }
    }

    return 0;
}
