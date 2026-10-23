// BY COOLDOT4!

#include <stdio.h>
#include <raylib.h>

// Fonction qui centre un texte horizontalement
void DrawTextCentered(const char *texte, int y, int taille, Color couleur)
{
    int largeur = MeasureText(texte, taille);
    int x = (GetScreenWidth() - largeur) / 2;

    DrawText(texte, x, y, taille, couleur);
}

int main(void)
{

    InitWindow(800, 600, "CatchTheSquare");
    SetTargetFPS(60);

    InitAudioDevice();

    Sound catch = LoadSound("sounds/catch.wav");
    Sound end = LoadSound("sounds/end.wav");

    Music bg = LoadMusicStream("sounds/bg.wav");

    bg.looping = true;
    PlayMusicStream(bg);

    Image icone = LoadImage("icone.png");
    SetWindowIcon(icone);
    UnloadImage(icone);

    int compteur = 0;

    int tailleCarre = GetRandomValue(32, 72);

    Color fond = WHITE;

    int carreX = GetRandomValue(0, 800 - tailleCarre);
    int carreY = GetRandomValue(100, 520 - tailleCarre);

    float debutPartie = GetTime();

    bool endsound = false;

    float tempsBonus = 0.0f;

    while (!WindowShouldClose())
    {

        UpdateMusicStream(bg);

        Vector2 souris = GetMousePosition();

        float Temps = 5.0f + tempsBonus - (GetTime() - debutPartie);

        BeginDrawing();
        ClearBackground(fond);

        if (Temps > 0)
        {

            DrawRectangle(0, 100, 800, 420, LIGHTGRAY);

            DrawTextCentered("Catch The Square", 32, 32, GRAY);
            DrawTextCentered("Click on the square !", 64, 20, GRAY);
            DrawText(TextFormat("Time : %.0fs", Temps), 10, 64, 24, GRAY);

            // Dessin du carré avec sa taille actuelle (stable)
            DrawRectangle(carreX, carreY, tailleCarre, tailleCarre, GRAY);

            // --- GESTION DU CLIC ---
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && souris.x >= carreX && souris.x <= carreX + tailleCarre && souris.y >= carreY && souris.y <= carreY + tailleCarre)
            {

                compteur++;
                tempsBonus += 1.0f;
                PlaySound(catch);

                // 1. On change d'abord la taille du carré pour le prochain coup
                tailleCarre = GetRandomValue(32, 72);

                // 2. On calcule la position en utilisant la NOUVELLE taille
                carreX = GetRandomValue(0, 800 - tailleCarre);
                carreY = GetRandomValue(100, 520 - tailleCarre);
            }

            // Gestion propre de la couleur du score
            if (compteur == 67)
            {
                DrawText(TextFormat("Score : %d", compteur), 10, 32, 24, RED);
            }
            else
            {
                DrawText(TextFormat("Score : %d", compteur), 10, 32, 24, GRAY);
            }

            DrawTextCentered("By COOLDOT4", 530, 16, LIGHTGRAY);
        }
        else
        {
            // Si endsound est FALSE, ça veut dire qu'on n'a pas encore joué le son de fin
            if (endsound == false)
            {
                StopMusicStream(bg);
                PlaySound(end);
                endsound = true;
            }

            ClearBackground(fond);
            DrawRectangle(0, 0, 800, 600, BLACK);
            DrawTextCentered("GAME OVER", 250, 56, RED);
            DrawTextCentered(TextFormat("Final Score : %d", compteur), 320, 24, WHITE);

            DrawTextCentered("Press SPACE to RESTART", 600 - 128, 24, WHITE);

            if (IsKeyPressed(KEY_SPACE))
            {

                compteur = 0;
                tempsBonus = 0.0f;
                debutPartie = GetTime();

                tailleCarre = GetRandomValue(32, 72);
                carreX = GetRandomValue(0, 800 - tailleCarre);
                carreY = GetRandomValue(100, 520 - tailleCarre);

                endsound = false;

                PlayMusicStream(bg);
            }
        }

        EndDrawing();
    }

    UnloadMusicStream(bg);
    UnloadSound(end);
    UnloadSound(catch);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

// my code could be more readable by adding some functions, but it'll be for another update.