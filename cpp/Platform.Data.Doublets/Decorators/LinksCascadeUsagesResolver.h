﻿namespace Platform::Data::Doublets::Decorators
{
    template <typename ...> class LinksCascadeUsagesResolver;
    template <typename TLink> class LinksCascadeUsagesResolver<TLink> : public LinksDecoratorBase<TLink>
    {
        public: LinksCascadeUsagesResolver(ILinks<TLink> &storage) : LinksDecoratorBase(storage) { }

        public: void Delete(CList auto&&restrictions) override
        {
            auto linkIndex = restrictions[_constants.IndexPart];
            _facade.DeleteAllUsages(linkIndex);
            _links.Delete(linkIndex);
        }
    };
}
