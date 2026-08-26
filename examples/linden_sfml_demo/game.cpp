#include "game.hpp"

#include <algorithm>
#include <numeric>
#include <random>

namespace game
{
    MemoryGame::MemoryGame(uint32_t pairCount)
        : _cardIds(pairCount), _pairCount(pairCount),
          _rng(std::random_device{}())
    {
        reset();
    }

    void MemoryGame::reset()
    {
        _cardIds.clear();
        _cardIds.resize(_pairCount * 2);
        _selected.clear();
        _selected.reserve(2);

        for (uint16_t value = 1; value <= _pairCount; ++value)
        {
            const auto index = static_cast<std::size_t>((value - 1) * 2);
            _cardIds[index] = value;
            _cardIds[index + 1] = value;
        };

        std::shuffle(_cardIds.begin(), _cardIds.end(), _rng);
    }

    uint32_t MemoryGame::getPairCount() const
    {
        return _pairCount;
    }

    const std::vector<uint32_t> &MemoryGame::getCardIds() const
    {
        return _cardIds;
    }

    void MemoryGame::selectCard(uint32_t idx)
    {
        if (idx >= _cardIds.size())
        {
            // TODO: Throw exceptions
            return;
        }

        if (_selected.size() == 2)
        {
            // TODO: Exception?
            return;
        }

        if (isSelected(idx))
        {
            return;
        }

        _selected.push_back(idx);
    }

    bool MemoryGame::isSelected(uint32_t idx) const
    {
        return std::find(_selected.begin(), _selected.end(), idx) !=
               _selected.end();
    }

    bool MemoryGame::turnAvailable() const
    {
        return _selected.size() == 2;
    }

    void MemoryGame::makeTurn()
    {
        if (checkTurn())
        {
            _cardIds[_selected[0]] = 0;
            _cardIds[_selected[1]] = 0;
            _score++;
        }
        _selected.clear();
    }

    bool MemoryGame::checkTurn() const
    {
        if (_selected.size() != 2)
        {
            return false;
        }

        return _cardIds[_selected[0]] == _cardIds[_selected[1]];
    }

    const uint32_t MemoryGame::getScore() const
    {
        return _score;
    }
} // namespace game