#pragma once
#include "TileMap.h"

template <class T>
class EntityManager
{
private:
	std::vector<std::shared_ptr<T>> entities;

	Texture texture;
	Vector2u entitySize;
	Collider entityCollider;
public:
	EntityManager()
	{
	}

	EntityManager(const Texture &texture, const Vector2u &entitySize, const Collider &entityCollider)
	{
		this->texture = texture;
		this->entitySize = entitySize;
		this->entityCollider = entityCollider;
	}

	const std::vector<std::shared_ptr<T>> &getEntities() const
	{
		return entities;
	}

	void push(const T &entity)
	{
		entities.push_back(std::make_shared<T>(entity));
	}

	void erase(const std::shared_ptr<T> &entity)
	{
		int idx = std::find(entities.begin(), entities.end(), entity) - entities.begin();
		entities.erase(entities.begin() + idx);
	}

	const Texture &getTexture() const
	{
		return texture;
	}

	const Vector2u &getSize() const
	{
		return entitySize;
	}

	const Collider &getCollider() const
	{
		return entityCollider;
	}

	void draw(RenderWindow &window)
	{
		for (auto &entity : entities)
		{
			window.draw(*entity);
		}
	}

	T *find(const Vector2f &pos)
	{
		for (auto &entity : entities)
		{
			if (entity->getPosition() == pos)
				return entity.get();
		}
		return NULL;
	}

	void reset()
	{
		entities.clear();
	}
};

