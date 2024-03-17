#include "../headers/Player.h"

/**
* \brief The method that monitors keystrokes
* \param event The active event
*/
void Player::Keys(sf::Event event)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
    {
        setStepx(-10.0f);
        if (StickAnim.GetCurrentAnimationName() != "idleBack") StickAnim.SwitchAnimation("idleBack");
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        setStepx(10.0f);
        if (StickAnim.GetCurrentAnimationName() != "idleForward") StickAnim.SwitchAnimation("idleForward");
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
        if (bOnGround) {
            setStepy(-2.4f);

            bOnGround = false;
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

/**
* \brief The method that controles collision of the player
* \param fDir Direction of the movement
*/
void Player::Collision(float fDir)
{
    for (int i = (SStickSprite.getPosition().y + fOffsetY) / stc_nTs; i < (SStickSprite.getPosition().y  + stc_nHeight + fOffsetY) / stc_nTs; i++)
        for (int j = (SStickSprite.getPosition().x + fOffsetX) / stc_nTs; j < (SStickSprite.getPosition().x  + stc_nWidth + fOffsetX) / stc_nTs; j++)
        {
            if (vecMap[i][j] == 'A')
            {
                if (fStepx > 0 && fDir == 0)
                {
                    SStickSprite.setPosition(j * stc_nTs - fOffsetX - stc_nWidth, SStickSprite.getPosition().y);
                }
                if (fStepx < 0 && fDir == 0)
                {
                    SStickSprite.setPosition(j * stc_nTs - fOffsetX + stc_nTs, SStickSprite.getPosition().y);
                }
                if (fStepy > 0 && fDir == 1)
                {
                    SStickSprite.setPosition(SStickSprite.getPosition().x, i * stc_nTs - fOffsetY - stc_nHeight);
                    setStepy(0);
                    bOnGround = true;
                }
                if (fStepy < 0 && fDir == 1)
                {
                    SStickSprite.setPosition(SStickSprite.getPosition().x, i * stc_nTs - fOffsetY + stc_nTs);
                    setStepy(0);
                }
            }

            if (vecMap[i][j] == 'o')
            {
                vecMap[i][j] = ' ';
                setPoints(getPoints() + 1);
            }

            if (vecMap[i][j] == 'D')
            {
                setDoorOpened(true);
            }
        }
}

/**
* \brief The method that updates game
* \param TDeltaTime Delta time
*/
void Player::Update(sf::Time const& TDeltaTime)
{
    // Show animation if player is alive 
    if (!bDead) StickAnim.Update(TDeltaTime);

    TTimeUpdate += TDeltaTime;

    if (TTimeUpdate > sf::milliseconds(2))
    {
        TTimeUpdate = sf::milliseconds(0);

        if (!bDead)
        {

            SStickSprite.setPosition(SStickSprite.getPosition().x + fStepx, SStickSprite.getPosition().y);

            Collision(0);

            if (!bOnGround) fStepy += 0.015f;

            SStickSprite.setPosition(SStickSprite.getPosition().x, SStickSprite.getPosition().y + fStepy);

            bOnGround = false;
            Collision(1);
            
            setStepx(0);
        }
        else
        {
            if (StickAnim.getEndAnim()) {
                SStickSprite.setRotation(90);
                SStickSprite.move(0, 7); 
            }
        }
    }
}