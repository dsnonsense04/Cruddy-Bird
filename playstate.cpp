#include "raylib.h"
#include "playstate.hpp"
#include "menustate.hpp"
#include "uibutton.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "bird.hpp"
#include "feces.hpp"
#include "gameoverstate.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

PlayState::PlayState(StateManager* manager)
    : back_button("Back", 10, 10, 100, 50),
      state_manager(manager)
    {
        this->spritesheet = LoadTexture("assets/textures/CruddyBird_SpriteSheet.png");
        this->background = LoadTexture("assets/textures/CruddyBird_GameBackground.png");
        SetTextureFilter(spritesheet, TEXTURE_FILTER_POINT);

        this->sound_defecate = LoadSound("assets/sound/defecate_sfx.wav");
        this->sound_explode = LoadSound("assets/sound/explosion_sfx.wav");
        this->sound_shoot = LoadSound("assets/sound/shoot_sfx.wav");

        this->player = new Player(this->spritesheet, 640 / 2 - 96, 340);

        this->bird_amount = 10;

        for (int i = 0; i < bird_amount; i++) {
            int species = GetRandomValue(1, 3);
            if (species == 1)
                birds.emplace_back(this->spritesheet, BirdSpecies::BlueJay, GetRandomValue(0, 640), 50);
            else if (species == 2)
                birds.emplace_back(this->spritesheet, BirdSpecies::Cardinal, GetRandomValue(0, 640), 50);
            else if (species == 3)
                birds.emplace_back(this->spritesheet, BirdSpecies::Duck, GetRandomValue(0, 640), 50);
        }

        this->should_defecate = false;
        this->defecate_chance = 0;
        this->defecate_cooldown = 1.5f;
    }

PlayState::~PlayState() {
    delete this->player;

    UnloadTexture(this->spritesheet);
    UnloadTexture(this->background);

    UnloadSound(this->sound_defecate);
    UnloadSound(this->sound_explode);
    UnloadSound(this->sound_shoot);
}

void PlayState::shoot() {
    Vector2 bullet_position = {
        player->get_position().x + 44,
        player->get_position().y
    };

    bullets.emplace_back(this->spritesheet, bullet_position);

    PlaySound(this->sound_shoot);
}

void PlayState::handle_input() {
    back_button.handle_input();

    if (back_button.is_clicked()) {
        state_manager->change_state(std::make_unique<MenuState>(state_manager));
    }

    if (IsKeyPressed(KEY_SPACE))
        shoot();
}

void PlayState::render() {
    Rectangle background_source = { 0, 0, 635, 360 };
    Rectangle background_scaling = { 0, 0, 640, 480 };
    DrawTexturePro(this->background, background_source, background_scaling, {0, 0}, 0.0f, WHITE);

    back_button.render();

    this->player->render();

    for (Bullet& bullet : bullets) {
        bullet.render();
    }

    for (Bird& bird : birds) {
        bird.render();
    }

    for (Explosion& explosion : explosions) {
        explosion.render();
    }

    for (Feces& feces : v_feces) {
        feces.render();
    }
}

void PlayState::tick(float delta_time) {
    this->player->tick(delta_time);

    // Game over logic.
    if (player->get_health() <= 0) {
        state_manager->change_state(std::make_unique<GameOverState>(state_manager));
        return;
    }

    // Defecating logic.
    this->defecate_cooldown -= delta_time;
    if (this->defecate_cooldown <= 0.0f && !birds.empty()) {
        // Pick one random bird.
        int bird_index = GetRandomValue(0, birds.size() - 1);

        // Spawn one piece of feces from that bird.
        v_feces.emplace_back(this->spritesheet, birds[bird_index].get_position());

        PlaySound(this->sound_defecate);

        // Wait a random amount of time before another bird defecates.
        this->defecate_cooldown = GetRandomValue(2, 3);
    }

    // Update bullets.
    for (Bullet& bullet : bullets) {
        bullet.tick(delta_time);
    }

    // Update birds.
    for (Bird& bird : birds) {
        bird.tick(delta_time);
    }

    // Update feces.
    for (Feces& feces : v_feces) {
        feces.tick(delta_time);
    }

    // Check for Bullet-Bird collisions.
    for (Bullet& bullet : this->bullets) {
        if (bullet.is_dead())
            continue;
        for (Bird& bird : this->birds) {
            if (bird.is_dead())
                continue;
            if (CheckCollisionRecs(bullet.get_dimensions(), bird.get_dimensions())) {
                // Create explosion where the bird was.
                this->explosions.emplace_back(this->spritesheet, bird.get_position());

                PlaySound(this->sound_explode);

                // Destroy both objects.
                bullet.destroy();
                bird.destroy();

                // This bullet already hit something, stop checking it against other Birds.
                break;
            }
        }
    }

    // Check for Player-Feces collisions.
    for (Feces& feces : v_feces) {
        if (CheckCollisionRecs(player->get_dimensions(), feces.get_dimensions())) {
            player->set_health(player->get_health() - 0.5f);

            // Only check one feces for collision at a time. If colliding, then stop checking.
            break;
        }
    }

    // Remove dead bullets.
    this->bullets.erase(
        std::remove_if(
            this->bullets.begin(),
            this->bullets.end(),
            [](Bullet& bullet)
            {
                return bullet.is_dead();
            }
        ),
        this->bullets.end()
    );

    // Remove bullets that have left the screen.
    bullets.erase(
        std::remove_if(
            bullets.begin(),
            bullets.end(),
            [](Bullet& bullet)
            {
                return bullet.is_off_screen();
            }
        ),
        bullets.end()
    );

    // Update explosions.
    for (Explosion& explosion : this->explosions) {
        explosion.tick(delta_time);
    }

    // Remove finished explosions.
    this->explosions.erase(
        std::remove_if(
            this->explosions.begin(),
            this->explosions.end(),
            [](Explosion& explosion)
            {
                return explosion.is_finished();
            }
        ),
        this->explosions.end()
    );

    // Remove dead birds.
    this->birds.erase(
        std::remove_if(
            this->birds.begin(),
            this->birds.end(),
            [](Bird& bird)
            {
                return bird.is_dead();
            }
        ),
        this->birds.end()
    );
}

void PlayState::on_enter() {
}

void PlayState::on_exit() {
}
