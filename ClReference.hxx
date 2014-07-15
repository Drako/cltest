#ifndef CLREFERENCE_HXX
#define CLREFERENCE_HXX

#include <atomic>
#include <utility>

namespace cl
{
    template <typename Type>
    class Reference
    {
        struct Container
        {
            Type * pointee_;
            std::atomic<unsigned> refcounter_;

            Container(Type * p, unsigned rc)
                : pointee_(p)
                , refcounter_(rc)
            {
            }
        };

    public:
        Reference()
            : container_ { new Container { nullptr, 0 }}
        {
        }

        explicit Reference(Type * object)
            : container_ { new Container { object, 1 }}
        {
        }

        Reference(Reference const & source)
            : container_ { source.container_ }
        {
            if (container_->pointee_)
                ++(container_->refcounter_);
        }

        Reference(Reference && source)
            : container_ { source.container_ }
        {
            source.container_ = nullptr;
        }

        ~Reference()
        {
            cleanup();
        }

        Reference & operator = (Reference const & source)
        {
            if (&source == this)
                return (*this);

            cleanup();

            container_ = source.container_;
            ++(container_->refcounter_);

            return (*this);
        }

        Reference & operator = (Reference && source)
        {
            if (&source == this)
                return (*this);

            cleanup();

            container_ = source.container_;
            source.container_ = nullptr;

            return (*this);
        }

        bool operator ! () const
        {
            return (container_ && container_->pointee_);
        }

        bool operator == (Reference const & other) const
        {
            return (container_ == other.container_);
        }

        bool operator != (Reference const & other) const
        {
            return (container_ != other.container_);
        }

        Type * operator -> () const
        {
            return (container_->pointee_);
        }

        Type & operator * () const
        {
            return *(container_->pointee_);
        }

    private:
        void cleanup()
        {
            if (container_->pointee_)
            {
                if ((container_->refcounter_)-- == 1)
                    delete container_->pointee_;
            }
            delete container_;
        }

        Container volatile * container_;
    };

    template <typename Base, typename Derived, typename... ArgTypes>
    Reference<Base> make_ref(ArgTypes&&... Args)
    {
        return Reference<Base>(new Derived(std::forward<ArgTypes>(Args)...));
    }
}

#endif // CLREFERENCE_HXX
