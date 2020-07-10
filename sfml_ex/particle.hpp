#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count) : m_particles(count), m_vertices(sf::Points, count), m_lifetime(sf::seconds(3)), m_emitter(0, 0)
    { }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // particle�� �����ֱ�(lifetime) ����
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // particle�� �׾��ִٸ� �ǻ츲
            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            // �ش� vertex�� ��ġ ����
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // particle�� ���� ���� alpha(����) ����
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();

            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // transform ����
        states.transform *= getTransform();

        // our particles don't use a texture 
        states.texture = NULL;

        // vertex array �׸���
        target.draw(m_vertices, states);
    }
private:
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // particle �� ���� �ӵ�(velocity)�� �����ֱ⸦ �ο�
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

        // �ش� vertex�� ��ġ �缳��
        m_vertices[index].position = m_emitter;
    }
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};