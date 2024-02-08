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

void Player::update(sf::Time const& TDeltaTime)
{
    // show animation if player is alive 
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