#include "LayerConcept.h"

namespace Lavender
{
    SubIdea* LayerConcept<SubIdea>::AddNew(const Idea* source)
    {
        m_Concepts.push_back(move(make_unique<SubIdea>(source)));
        return m_Concepts[m_Concepts.size() - 1].get();
    }
    Info* LayerConcept<Info>::AddNew(const Idea* source)
    {
        m_Concepts.push_back(move(make_unique<Info>(source)));
        return m_Concepts[m_Concepts.size() - 1].get();
    }
    Idea* LayerConcept<Idea>::AddNew(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    {
        m_Concepts.push_back(move(make_unique<Idea>(position, rotation, scale)));
        return m_Concepts[m_Concepts.size() - 1].get();
    }
}