#pragma once

#include "base_transition.hpp"
#include <memory>
#include <vector>

namespace linden::tweening
{
    template <typename ValueT>
    class SequenceTransition : public BaseTransition<ValueT>
    {
    private:
        std::vector<std::unique_ptr<BaseTransition<ValueT>>> _transitions{};
        size_t _idx{};

    public:
        ~SequenceTransition() = default;

        UpdateResult update(ValueT elapsedValue)
        {
            UpdateResult retval = _transitions[_idx]->update(elapsedValue);

            if (retval.state == TransitionState::Done)
            {
                if (++_idx >= _transitions.size())
                {
                    return retval;
                }
            }

            retval.state = TransitionState::Running;
            return retval;
        }

        template <typename T, typename... Args>
            requires std::derived_from<T,
                                       linden::tweening::BaseTransition<ValueT>>
        void addTransition(Args &&...args)
        {
            _transitions.emplace_back(
                std::make_unique<T>(std::forward<Args>(args)...));
        }
    };
} // namespace linden::tweening