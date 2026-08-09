#include <cstdint>
#include <random>
#include <vector>

namespace game
{
    class MemoryGame
    {
    private:
        uint32_t _pairCount;
        std::vector<uint32_t> _cardIds;
        std::vector<uint32_t> _selected;

        std::mt19937 _rng;

        uint32_t _score{};

    public:
        MemoryGame(uint32_t cardCount);

        // Game management
        void reset();

        // Data retrieval
        uint32_t getPairCount() const;
        const std::vector<uint32_t> &getCardIds() const;
        const uint32_t getScore() const;

        // Turn moves
        void selectCard(uint32_t idx);
        bool isSelected(uint32_t idx) const;
        bool turnAvailable() const;
        void makeTurn();
        bool checkTurn() const;
    };
} // namespace game