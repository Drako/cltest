#include "ClPlatforms.hxx"

namespace cl
{
    PlatformIterator::PlatformIterator(Platforms const * platforms /* = nullptr */, unsigned index /* = 0 */)
        : platforms(platforms)
        , index(index)
    {
        if (!platforms || index >= platforms->count())
        {
            this->platforms = nullptr;
            this->index = 0;
        }
    }

    bool PlatformIterator::operator == (PlatformIterator const & rhs) const
    {
        return (platforms == rhs.platforms && index == rhs.index);
    }

    bool PlatformIterator::operator != (PlatformIterator const & rhs) const
    {
        return (platforms != rhs.platforms || index != rhs.index);
    }

    PlatformIterator PlatformIterator::operator ++ (int)
    {
        PlatformIterator old(*this);
        if (platforms && (index < platforms->count()))
        {
            if (++index == platforms->count())
            {
                platforms = nullptr;
                index = 0;
            }
        }
        return old;
    }

    PlatformIterator & PlatformIterator::operator ++ ()
    {
        if (platforms && (index < platforms->count()))
        {
            if (++index == platforms->count())
            {
                platforms = nullptr;
                index = 0;
            }
        }
        return (*this);
    }

    Reference<Platform> PlatformIterator::operator * () const
    {
        if (!platforms || index > platforms->count())
            return Reference<Platform>();
        return (*platforms)[index];
    }
}
