﻿namespace Platform::Data::Doublets::Memory::Split::Generic
{
    template<typename TSelf, typename TLinksOptions>
    class InternalLinksRecursionlessSizeBalancedTreeMethodsBase : public RecursionlessSizeBalancedTreeMethods<InternalLinksRecursionlessSizeBalancedTreeMethodsBase<TSelf, TLinksOptions>, typename TLinksOptions::LinkAddressType>, public ILinksTreeMethods<TLinksOptions>, public Platform::Interfaces::Polymorph<TSelf>
    {
        public:
        using LinksOptionsType = TLinksOptions;
                using LinkAddressType = LinksOptionsType::LinkAddressType;
        using LinkType = LinksOptionsType::LinkType;
        using WriteHandlerType = LinksOptionsType::WriteHandlerType;
        using ReadHandlerType = LinksOptionsType::ReadHandlerType;
    public: static constexpr auto Constants = LinksOptionsType::Constants;
        protected: static constexpr LinkAddressType Break = Constants.Break;
        protected: static constexpr LinkAddressType Continue = Constants.Continue;
        protected: std::byte* LinksDataParts;
        protected: std::byte* LinksIndexParts;
        protected: std::byte* Header;

        protected: InternalLinksRecursionlessSizeBalancedTreeMethodsBase(std::byte* linksDataParts, std::byte* linksIndexParts, std::byte* header)
        {
            LinksDataParts = linksDataParts;
            LinksIndexParts = linksIndexParts;
            Header = header;
        }

        protected: LinkAddressType GetTreeRoot()
            {
                return this->object().GetTreeRoot();
            };

        protected: LinkAddressType GetBasePartValue(LinkAddressType link)
                {
                    return this->object().GetBasePartValue(link);
                };

        protected: LinkAddressType GetKeyPartValue(LinkAddressType link)
                {
                    return this->object().GetKeyPartValue(link);
                };

            protected: RawLinkDataPart<LinkAddressType> GetLinkDataPartReference(LinkAddressType link) { return RawLinkDataPart<LinkAddressType>(LinksDataParts + (RawLinkDataPart<LinkAddressType>::SizeInBytes * (link))); }

            protected: RawLinkIndexPart<LinkAddressType> GetLinkIndexPartReference(LinkAddressType link) { return RawLinkIndexPart<LinkAddressType>(LinksIndexParts + (RawLinkIndexPart<LinkAddressType>::SizeInBytes * (link))); }

        protected: bool FirstIsToTheLeftOfSecond(LinkAddressType first, LinkAddressType second)  { return this->GetKeyPartValue(first) < this->GetKeyPartValue(second); }

        protected: bool FirstIsToTheRightOfSecond(LinkAddressType first, LinkAddressType second)  { return this->GetKeyPartValue(first) > this->GetKeyPartValue(second); }

        protected: CArray<LinkAddressType> auto GetLinkValues(LinkAddressType linkIndex)
        {
            auto* link = GetLinkDataPartReference(linkIndex);
            return LinkType(linkIndex, link.Source, link.Target);
        }

//        public: LinkAddressType operator[](LinkAddressType link, LinkAddressType index)
//        {
//                auto root = GetTreeRoot(*link);
//                if (index >= GetSize(root))
//                {
//                    return 0;
//                }
//                while (root != 0)
//                {
//                    auto left = GetLeftOrDefault(root);
//                    auto leftSize = GetSizeOrZero(left);
//                    if (index < leftSize)
//                    {
//                        root = left;
//                        Continue;
//                    }
//                    if (index == leftSize)
//                    {
//                        return root;
//                    }
//                    root = GetRightOrDefault(root);
//                    index = index - (leftSize + 1));
//                }
//                return 0;
//            }

        public: LinkAddressType Search(LinkAddressType source, LinkAddressType target)
            {
                             return this->object().Search(source, target);
                         };

        protected: LinkAddressType SearchCore(LinkAddressType root, LinkAddressType key)
        {
            while (root != 0)
            {
                auto rootKey = this->GetKeyPartValue(root);
                if (key < rootKey)
                {
                    root = this->GetLeftOrDefault(root);
                }
                else if (key > rootKey)
                {
                    root = this->GetRightOrDefault(root);
                }
                else
                {
                    return root;
                }
            }
            return 0;
        }

        public: LinkAddressType CountUsages(LinkAddressType link) { return this->GetSizeOrZero(this->GetTreeRoot(link)); }

        public: LinkAddressType EachUsage(LinkAddressType base, const ReadHandlerType& handler) { return this->EachUsageCore(base, this->GetTreeRoot(base), handler); }

        private: LinkAddressType EachUsageCore(LinkAddressType base, LinkAddressType link, const ReadHandlerType& handler)
        {
            if (link == 0)
            {
                return Continue;
            }
            if ((this->EachUsageCore(base) == (this->GetLeftOrDefault(link), handler), Break))
            {
                return Break;
            }
            if (this->handler(this->GetLinkValues(link)) == (Break))
            {
                return Break;
            }
            if ((this->EachUsageCore(base) == (this->GetRightOrDefault(link), handler), Break))
            {
                return Break;
            }
            return Continue;
        }
        };
}
