#include "Collition_System.hpp"

Collition_System::Collition_System(Player& player, vector<Enemy>& enemies, vector<Blocks>& blocks, vector<Collectibles>& collectibles) : 
    player(player), 
    enemies(enemies), 
    blocks(blocks),
    collectibles(collectibles) {}

void Collition_System::CheckPlayerCollitions() {
        Rectangle playerRect = player.GetRect();

        for(Enemy& enemy : enemies) {
            Rectangle enemyRect = enemy.GetRect();

            // Enemy collition system
            if (enemy.IsAlive()) {
                if (CheckCollisionRecs(playerRect, enemyRect)) {
                    // Verify if the player is falling over the enemy (stomping)
                    bool isStomping = (playerRect.y + playerRect.height < enemyRect.y + 20) && (player.isFalling());

                    if (isStomping) {
                        // Stomping effect
                        player.Jump();
                        enemy.TakeDamage();
                    } 
                    else {
                        // lateral collition
                        player.knockback(enemyRect);
                    }
                }
            }
        }
        

        // Blocks collition system
        // Reset wall state for this frame
        player.SetTouchingWallHorizontally(false);

        for (Blocks& block : blocks) {
            Rectangle blockRect = block.GetRect();
            Rectangle playerRect = player.GetRect();
            
            if (CheckCollisionRecs(playerRect, blockRect)) {
                // Find the center points to determine collision direction
                // Player center point
                float playerCenterX = playerRect.x + playerRect.width / 2;
                float playerCenterY = playerRect.y + playerRect.height / 2;

                // Block center point
                float blockCenterX = blockRect.x + blockRect.width / 2;
                float blockCenterY = blockRect.y + blockRect.height / 2;
                
                // Calculate distance between centers
                float deltaX = playerCenterX - blockCenterX;
                float deltaY = playerCenterY - blockCenterY;
                
                // The bigger difference tells us which side we hit
                float horizontalBias = 1.1f; 
                // With this bias we priorize the horizontal collition. 
                // Because sometimes the comparation bellow can be equal (5 = 5) 
                // so it will be detected as vertical collition instead horizontal. 
                
                if ( (abs(deltaX) * horizontalBias) > abs(deltaY)) {
                    // Horizontal collision - we hit the left or right side
                    if (deltaX > 0) {
                        // Player is to the right, push them further right
                        player.SetPosition(blockRect.x + blockRect.width, playerRect.y);
                    } else {
                        // Player is to the left, push them further left
                        player.SetPosition(blockRect.x - playerRect.width, playerRect.y);
                    }
                    player.SetTouchingWallHorizontally(true);
                } else {
                    // Vertical collision - we hit the top or bottom
                    if (deltaY > 0) {
                        // Player is below block - bonk! (head bump)
                        player.SetPosition(playerRect.x, blockRect.y + blockRect.height);
                        player.SetVelocityY(0);
                    } else {
                        // Player is above block - landing platform
                        // Only snap to platform if we're actually falling down
                        if (player.isFalling()) {
                            player.SetPosition(playerRect.x, blockRect.y - playerRect.height);
                            player.SetVelocityY(0);
                            player.SetJumping(false);
                        }
                    }
                }
            }
        }

        // Collectibles collition system
        for (Collectibles& collectible : collectibles) {
            Rectangle collectibleRect = collectible.GetRect();
            Rectangle playerRect = player.GetRect();

            if (CheckCollisionRecs(playerRect, collectibleRect) && !collectible.IsCollected()) {
                collectible.Collect();
            }
        }
    }

void Collition_System::CheckEnemyCollitions() {

    for(Enemy& enemy : enemies) {
        enemy.SetTouchingWallHorizontally(false);

            for (Blocks& block : blocks) {
                Rectangle blockRect = block.GetRect();
                Rectangle enemyRect = enemy.GetRect();
                
                if (CheckCollisionRecs(enemyRect, blockRect)) {
                    // Find the center points to determine collision direction
                    // enemy center point
                    float enemyCenterX = enemyRect.x + enemyRect.width / 2;
                    float enemyCenterY = enemyRect.y + enemyRect.height / 2;

                    // Block center point
                    float blockCenterX = blockRect.x + blockRect.width / 2;
                    float blockCenterY = blockRect.y + blockRect.height / 2;
                    
                    // Calculate distance between centers
                    float deltaX = enemyCenterX - blockCenterX;
                    float deltaY = enemyCenterY - blockCenterY;
                    
                    // The bigger difference tells us which side we hit
                    float VerticalBias = 1.1f; 
                    // With this bias we prioritize the vertical collision for enemies.
                    // Because enemies move continuously, they often land in positions where
                    // deltaX ≈ deltaY. Without this bias, landing collisions could be incorrectly  
                    // detected as horizontal, causing enemies to stick to block sides instead
                    // of standing on top of them.
                    
                    if ( abs(deltaX) > (abs(deltaY) * VerticalBias)) {
                        // Horizontal collision - we hit the left or right side
                        if (deltaX > 0) {
                            // enemy is to the right, push them further right
                            enemy.SetPosition(blockRect.x + blockRect.width, enemyRect.y);
                        } else {
                            // enemy is to the left, push them further left
                            enemy.SetPosition(blockRect.x - enemyRect.width, enemyRect.y);
                        }
                        enemy.SetTouchingWallHorizontally(true);
                    } else {
                        // Vertical collision - we hit the top or bottom
                        if (deltaY > 0) {
                            // enemy is below block - bonk! (head bump)
                            enemy.SetPosition(enemyRect.x, blockRect.y + blockRect.height);
                            enemy.SetVelocityY(0);
                        } else {
                            // enemy is above block - landing platform
                            // Only snap to platform if we're actually falling down
                            if (enemy.isFalling()) {
                                enemy.SetPosition(enemyRect.x, blockRect.y - enemyRect.height);
                                enemy.SetVelocityY(0);
                                enemy.SetJumping(false);
                            }
                        }
                    }
                }
            }
    }
}

