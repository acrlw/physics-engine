#ifndef ALBODY_H
#define ALBODY_H

#include <almath.h>
#include <alsettings.h>
#include <vector>
#include <QDebug>

enum BodyType
{
    None,
	Circle,
	Polygon,
	Wall
};

class alBody
{
public:
    alBody(const BodyType type = BodyType::None, const float m = 1, const bool sleep = true, const bool touched = false):
        m_sleep(sleep), m_isTouched(touched), m_mass(m), m_torque(0), m_angle(0),
        m_angularAcceleration(0), m_angularVelocity(0), m_type(type)
	{
	}

	alVector2& velocity()
	{
		return m_velocity;
	}

	void setVelocity(const alVector2& velocity)
	{
		m_velocity = velocity;
	}

	alVector2& acceleration()
	{
		return m_acceleration;
	}

	void setAcceleration(const alVector2& acceleration)
	{
		m_acceleration = acceleration;
	}

	alVector2& position()
	{
		return m_position;
	}

	void setPosition(const alVector2& position)
	{
		m_position = position;
	}

	float mass() const
	{
		return m_mass;
	}

	void setMass(float mass)
	{
		m_mass = mass;
	}

	float angle() const
	{
		return m_angle;
	}

	void setAngle(float angle)
	{
		m_angle = angle;
	}

	float angularAcceleration() const
	{
		return m_angularAcceleration;
	}

	void setAngularAcceleration(float angularAcceleration)
	{
		m_angularAcceleration = angularAcceleration;
	}

	bool sleep() const
	{
		return m_sleep;
	}

	void setSleep(bool sleep)
	{
		m_sleep = sleep;
	}

	float angularVelocity() const
	{
		return m_angularVelocity;
	}

	void setAngularVelocity(float angularVelocity)
	{
		m_angularVelocity = angularVelocity;
	}

	void update()
	{
		if (!m_sleep)
		{
			alVector2 pos = m_position;
			alVector2 velocity = m_velocity;
			alVector2 acceleration;
			float angularAcceleraion = m_angularAcceleration;
			float angularVelocity = m_angularVelocity;
			float angle = m_angle;


			if (velocity.lengthSquare() < alStopThreshold) // if it did reach the deadline
				velocity.set(0., 0.);

			if (angularVelocity * angularVelocity < alStopThreshold)
				angularVelocity = 0;

			//acceleration = alVector2(0, 10) + m_forces / m_mass;
			//angularAcceleraion = m_torque / m_inertia;

			velocity += acceleration * alDeltaTime;
			angularVelocity += angularAcceleraion * alDeltaTime;

			pos += velocity;
			angle += angularVelocity;

			m_position = pos;
			m_angle = angle;
			m_velocity = velocity;
			m_angularVelocity = angularVelocity;


			m_forces.set(0, 0);
			m_torque = 0;
		}
	}

	BodyType type() const
	{
		return m_type;
	}

	void setType(const BodyType& type)
	{
		m_type = type;
	}

	bool isTouched() const
	{
		return m_isTouched;
	}

	void setIsTouched(bool isTouched)
	{
		m_isTouched = isTouched;
	}

	float inertia() const
	{
		return m_inertia;
	}

	void setInertia(float inertia)
	{
		m_inertia = inertia;
	}

	float density() const
	{
		return m_density;
	}

	void setDensity(float density)
	{
		m_density = density;
	}

	alVector2 massPosition() const
	{
		return m_massPosition;
	}

	void setMassPosition(const alVector2& massPosition)
	{
		m_massPosition = massPosition;
	}

	float torque() const
	{
		return m_torque;
	}

	void setTorque(float torque)
	{
		m_torque = torque;
	}

	alVector2 forces() const
	{
		return m_forces;
	}

	void setForces(const alVector2& forces)
	{
		m_forces = forces;
	}

	void clearForce()
	{
		m_forces.set(0, 0);
	}

	void addForce(const alVector2& force)
	{
		m_forces += force;
	}

protected:
	bool m_sleep;
	bool m_isTouched;
	float m_mass;
	float m_density;
	float m_inertia;
	float m_torque;
	float m_angle;
	float m_angularAcceleration;
	float m_angularVelocity;
	alVector2 m_massPosition;
	alVector2 m_velocity;
	alVector2 m_acceleration;
	alVector2 m_position;
	alVector2 m_forces;
	std::vector<alVector2> m_vertices;
	float m_radius;
	bool m_isConvex;
	BodyType m_type;
};

class alCircle : public alBody
{
public:
    alCircle(const float radius = 120, const float angle = 0, const float m = 1):
        alBody(BodyType::Circle)
	{
		m_angle = angle;
        m_mass = m;
		m_massPosition = m_position;
		m_inertia = m_mass * m_radius * m_radius * 0.5;
		m_radius = radius;
	}

	void setPosition(const alVector2& position)
	{
		m_position = position;
		m_massPosition = m_position;
	}

	float radius() const
	{
		return m_radius;
	}

	void setRadius(float radius)
	{
		m_radius = radius;
		m_inertia = m_mass * m_radius * m_radius * 0.5;
	}
};

class alPolygon : public alBody
{
public:
    alPolygon():
        alBody(BodyType::Polygon)
    {
		m_isConvex = true;
	}

	std::vector<alVector2>& vertices()
	{
		return m_vertices;
	}

	void setVertices(const std::vector<alVector2>& vertices)
	{
		m_vertices = vertices;
	}

	/// \brief
	/// return the rotated vertices of polygon
	/// \return
	std::vector<alVector2> getRotatedVertices() const
	{
		std::vector<alVector2> actual;
		foreach(alVector2 v, m_vertices)
		{
			alVector2 va = alRotation(m_angle) * v;
			actual.push_back(va);
		}
		return actual;
	}

	void addVertex(const alVector2& v)
	{
		m_vertices.push_back(v);
		updateMassPosition();
	}

	alVector2 triangleGravityPoint(const alVector2& a1, const alVector2& a2, const alVector2& a3) const
	{
		return alVector2(a1 + a2 + a3) / 3;
	}

	float triangleArea(const alVector2& a1, const alVector2& a2, const alVector2& a3) const
	{
		return abs(alCross2(a1 - a2, a1 - a3)) / 2;
	}

protected:
	///
	/// \brief updateMassPosition
	/// update the mass position
	void updateMassPosition()
	{
		if (m_vertices.size() >= 3)
		{
			if (m_type == Polygon)
			{
				alVector2 pos;
				float area = 0;
				for (int i = 0; i < m_vertices.size() - 1; i++)
				{
					float a = triangleArea(alVector2(0, 0), m_vertices[i], m_vertices[i + 1]);
					alVector2 p = triangleGravityPoint(alVector2(0, 0), m_vertices[i], m_vertices[i + 1]);
					pos += p * a;
					area += a;
				}
				pos /= area;
				m_massPosition = pos;
				updateInertia();
			}
		}
	}

	///
	/// \brief
	/// the vertices come from when body stay the origin static status, which means this vertices will not participate the transformation


private:
	void updateInertia()
	{
		float sum1 = 0.0;
		float sum2 = 0.0;
		for (int i = 0; i < m_vertices.size() - 1; i++)
		{
			alVector2 n1 = m_vertices[i] - m_massPosition;
			alVector2 n2 = m_vertices[i + 1] - m_massPosition;
			float cross = abs(alCross2(n1, n2));
			float dot = n2 * n2 + n2 * n1 + n1 * n1;
			sum1 += cross * dot;
			sum2 += cross;
		}
		m_inertia = (m_mass / 6) * sum1 / sum2;
	}
};

class alRectangle : public alPolygon
{
public:
    alRectangle(const float width = 50, const float height = 50):
        alPolygon(), m_width(width), m_height(height)
    {
		m_massPosition = m_position;
		updateVertices();
	}

	float width() const
	{
		return m_width;
	}

	void setWidth(float width)
	{
		m_width = width;
		updateVertices();
	}

	float height() const
	{
		return m_height;
	}

	void setHeight(float height)
	{
		m_height = height;
		updateVertices();
	}

	void updateVertices()
	{
		m_vertices.clear();
		addVertex(alVector2(-m_width / 2, m_height / 2));
		addVertex(alVector2(-m_width / 2, -m_height / 2));
		addVertex(alVector2(m_width / 2, -m_height / 2));
		addVertex(alVector2(m_width / 2, m_height / 2));
		addVertex(alVector2(-m_width / 2, m_height / 2));
		m_massPosition = m_position;
		updateInertia();
	}

protected:
	float m_width;
	float m_height;
private:
	void updateInertia()
	{
		m_inertia = m_mass * (m_width * m_width + m_height * m_height) / 12;
	}
};

class alWall : public alRectangle
{
public:
	alWall(const float elasticCoefficient = 0.8, const float width = 40): alRectangle(),
	                                                                      m_elasticCoefficient(elasticCoefficient)
	{
		m_type = Wall;
		m_width = width;
		m_height = width;
		m_massPosition = m_position;
	}

	float elasticCoefficient() const
	{
		return m_elasticCoefficient;
	}

	void setElasticCoefficient(float elasticCoefficient)
	{
		m_elasticCoefficient = elasticCoefficient;
	}

private:
	float m_elasticCoefficient;
};
#endif // ALBODY_H
