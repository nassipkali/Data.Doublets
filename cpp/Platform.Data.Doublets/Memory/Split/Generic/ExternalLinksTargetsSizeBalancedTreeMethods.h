﻿namespace Platform::Data::Doublets::Memory::Split::Generic
{
    template<typename TLinksOptions>
    class ExternalLinksTargetsSizeBalancedTreeMethods : public ExternalLinksSizeBalancedTreeMethodsBase<ExternalLinksTargetsSizeBalancedTreeMethods<TLinksOptions>, TLinksOptions>
    {
        public:
        using LinksOptionsType = TLinksOptions;
        using LinkAddressType = TLinksOptions::LinkAddressType;
        using base = ExternalLinksSizeBalancedTreeMethodsBase<ExternalLinksTargetsSizeBalancedTreeMethods<TLinksOptions>, TLinksOptions>;
        public: ExternalLinksTargetsSizeBalancedTreeMethods(std::byte* linksDataParts, std::byte* linksIndexParts, std::byte* header) : base(linksDataParts, linksIndexParts, header) { }

        protected: LinkAddressType* GetLeftReference(LinkAddressType node)  { return &GetLinkIndexPartReference(node)->LeftAsTarget; }

        protected: LinkAddressType* GetRightReference(LinkAddressType node)  { return &GetLinkIndexPartReference(node)->RightAsTarget; }

        protected: LinkAddressType GetLeft(LinkAddressType node)  { return this->GetLinkIndexPartReference(node)->LeftAsTarget; }

        protected: LinkAddressType GetRight(LinkAddressType node)  { return this->GetLinkIndexPartReference(node)->RightAsTarget; }

        protected: void SetLeft(LinkAddressType node, LinkAddressType left)  { this->GetLinkIndexPartReference(node)->LeftAsTarget = left; }

        protected: void SetRight(LinkAddressType node, LinkAddressType right)  { this->GetLinkIndexPartReference(node)->RightAsTarget = right; }

        protected: LinkAddressType GetSize(LinkAddressType node)  { return this->GetLinkIndexPartReference(node)->SizeAsTarget; }

        protected: void SetSize(LinkAddressType node, LinkAddressType size)  { this->GetLinkIndexPartReference(node)->SizeAsTarget = size; }

        protected:  LinkAddressType GetTreeRoot() { return this->GetHeaderReference().RootAsTarget; }

        public: LinkAddressType GetBasePartValue(LinkAddressType link)  { return this->GetLinkDataPartReference(link)->Target; }

        public: bool FirstIsToTheLeftOfSecond(LinkAddressType firstSource, LinkAddressType firstTarget, LinkAddressType secondSource, LinkAddressType secondTarget)  { return this->LessThan(firstTarget, secondTarget) || (firstTarget == secondTarget && this->LessThan(firstSource, secondSource)); }

        public: bool FirstIsToTheRightOfSecond(LinkAddressType firstSource, LinkAddressType firstTarget, LinkAddressType secondSource, LinkAddressType secondTarget)  { return firstTarget > secondTarget || (firstTarget == secondTarget && firstSource > secondSource); }

        protected: void ClearNode(LinkAddressType node)
        {
            auto& link = this->GetLinkIndexPartReference(node);
            link.LeftAsTarget = 0;
            link.RightAsTarget = 0;
            link.SizeAsTarget = 0;
        }
    };
}
