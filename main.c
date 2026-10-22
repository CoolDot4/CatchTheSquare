#include <stdio.h>
#include <raylib.h>

        // Fonction qui centre un texte horizontalement
    void DrawTextCentered(const char *texte, int y, int taille, Color couleur) {
        int largeur = MeasureText(texte, taille);
        int x = (GetScreenWidth() - largeur) / 2;

        DrawText(texte, x, y, taille, couleur);
    }

int main(void){

    InitWindow(800, 600 , "CatchTheSquare");
    SetTargetFPS(60);

    InitAudioDevice();

    Sound catch = LoadSound("sounds/catch.wav");
        
    Music bg = LoadMusicStream("sounds/bg.wav");

    bg.looping = true;
    PlayMusicStream(bg);

    Image icone = LoadImage("icone.png");
    SetWindowIcon(icone);
    UnloadImage(icone);

    int compteur = 0;
    int tailleCarre = 64;

    Color fond = WHITE;

    int carreX = GetRandomValue(0, 800 - tailleCarre); 
    int carreY = GetRandomValue(100, 520 - tailleCarre); 

    while (!WindowShouldClose()){

        UpdateMusicStream(bg);

        Vector2 souris = GetMousePosition();

        BeginDrawing();
        ClearBackground(fond);

            DrawRectangle(0, 100, 800, 420, LIGHTGRAY);

            DrawTextCentered("Catch The Square", 32, 32, GRAY);
            DrawTextCentered("Click on the square !", 64, 20, GRAY);

            if(compteur >= 50){
                
                tailleCarre = 32;

            } else {

                tailleCarre = 64;

            }

            DrawRectangle(carreX, carreY, tailleCarre, tailleCarre, GRAY);

    

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
            && souris.x >= carreX
            && souris.x <= carreX + tailleCarre
            && souris.y >= carreY 
            && souris.y <= carreY + tailleCarre) {
            compteur++;

            PlaySound(catch);

            carreX = GetRandomValue(0, 800 - tailleCarre); 
            carreY = GetRandomValue(100, 520 - tailleCarre); 

        }

            DrawText(TextFormat("Score : %d", compteur), 10, 32, 24, GRAY); 
            
            if(compteur == 67){
                DrawText(TextFormat("Score : %d", compteur), 10, 32, 24, RED);
            }

            DrawTextCentered("By COOLDOT4", 530, 16, LIGHTGRAY);
            
        EndDrawing();
    }
    
    UnloadMusicStream(bg);
    UnloadSound(catch);
    CloseAudioDevice();
    CloseWindow();
    return 0;

}