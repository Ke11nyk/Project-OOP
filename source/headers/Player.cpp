#include "Player.h"

void Player::Keys(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        setStepx(-10.0f);
        if (StickAnim.GetCurrentAnimationName() != "idleBack") StickAnim.SwitchAnimation("idleBack");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        setStepx(10.0f);
        if (StickAnim.GetCurrentAnimationName() != "idleForward") StickAnim.SwitchAnimation("idleForward");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        if (onGround) {
            setStepy(-2.4f);

            onGround = false;
        }

    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Right: {setStepx(0); if (StickAnim.GetCurrentAnimationName() != "idleForwardStatic") StickAnim.SwitchAnimation("idleForwardStatic"); }  break;
        case sf::Keyboard::Left: {setStepx(0); if (StickAnim.GetCurrentAnimationName() != "idleBackStatic") StickAnim.SwitchAnimation("idleBackStatic"); }  break;

        default:
            break;
        }
    }
}

void Player::Collision(float dir)
{
    for (int i = (StickSprite.getPosition().y + offsetY) / ts; i < (StickSprite.getPosition().y  + height + offsetY) / ts; i++)
        for (int j = (StickSprite.getPosition().x + offsetX) / ts; j < (StickSprite.getPosition().x  + width + offsetX) / ts; j++)
        {
            if (map[i][j] == 'A')
            {
                if (stepx > 0 && dir == 0)
                {
                    StickSprite.setPosition(j * ts - offsetX - width, StickSprite.getPosition().y);
                }
                if (stepx < 0 && dir == 0)
                {
                    StickSprite.setPosition(j * ts - offsetX + ts, StickSprite.getPosition().y);
                }
                if (stepy > 0 && dir == 1)
                {
                    StickSprite.setPosition(StickSprite.getPosition().x, i * ts - offsetY - height);
                    setStepy(0);
                    onGround = true;
                }
                if (stepy < 0 && dir == 1)
                {
                    StickSprite.setPosition(StickSprite.getPosition().x, i * ts - offsetY + ts);
                    setStepy(0);
                }
            }

            if (map[i][j] == 'o')
            {
                map[i][j] = ' ';
                setPoints(getPoints() + 1);
            }
        }
}

void Player::update(sf::Time const& deltaTime)
{
    // show animation if player is alive 
    if (!dead) StickAnim.Update(deltaTime);

    timeUpdate += deltaTime;

    if (timeUpdate > sf::milliseconds(2))
    {
        timeUpdate = sf::milliseconds(0);

        if (!dead)
        {

            StickSprite.setPosition(StickSprite.getPosition().x + stepx, StickSprite.getPosition().y);

            Collision(0);

            if (!onGround) stepy += 0.015f;

            StickSprite.setPosition(StickSprite.getPosition().x, StickSprite.getPosition().y + stepy);

            onGround = false;
            Collision(1);
            
            setStepx(0);
        }
        else
        {
            if (StickAnim.getEndAnim()) {
                StickSprite.setRotation(90);
                StickSprite.move(0, 7); 
            }
        }
    }
}