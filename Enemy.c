struct Enemy {
  int health;
  int xPos;
  int yPos;
  int ammo;
  int score;
  //Add field for image
};

struct Enemy spawnEnemy() {
struct Enemy enemy;
enemy.health = 10;
enemy.ammo = 5;
enemy.score = 0;
/* Set these two to correct starting position for enemy
enemy.xPos = 5;
enemy.yPos = 5;
*/
}

/*
void changeHealth(struct Enemy enemy, int change) {
  enemy.health += change;
}

void changeAmmo(struct Enemy enemy, int change) {
  enemy.ammo += change;
}

void increaseScore(struct Enemy enemy, int points) {
  enemy.score += points;
}

void jump(struct Enemy enemy) {
  //Somehow change the YPosition
  // Should be random if we want the enemies to jump.
}
*/