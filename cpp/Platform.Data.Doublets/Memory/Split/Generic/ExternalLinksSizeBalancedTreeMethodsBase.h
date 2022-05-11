﻿namespace Platform::Data::Doublets::Memory::Split::Generic
{
    template<typename TSelf, typename TLinksOptions>
    class ExternalLinksSizeBalancedTreeMethodsBase : public SizeBalancedTreeMethods<ExternalLinksSizeBalancedTreeMethodsBase<TSelf, TLinksOptions>, typename TLinksOptions::LinkAddressType>, public ILinksTreeMethods<TLinksOptions>, public Platform::Interfaces::Polymorph<TSelf>
    {
    public:
        using LinksOptionsType = TLinksOptions;
        static constexpr auto Constants = LinksOptionsType::Constants;
                using LinkAddressType = LinksOptionsType::LinkAddressType;
        using LinkType = LinksOptionsType::LinkType;
        using WriteHandlerType = LinksOptionsType::WriteHandlerType;
        using ReadHandlerType = LinksOptionsType::ReadHandlerType;
        protected: static constexpr LinkAddressType Break = Constants.Break;
        protected: static constexpr LinkAddressType Continue = Constants.Continue;
        protected: std::byte* LinksDataParts;
        protected: std::byte* LinksIndexParts;
        protected: std::byte* Header;

        protected: ExternalLinksSizeBalancedTreeMethodsBase(std::byte* linksDataParts, std::byte* linksIndexParts, std::byte* header)
        {
            LinksDataParts = linksDataParts;
            LinksIndexParts = linksIndexParts;
            Header = header;
            Break = Constants.Break;
            Continue = Constants.Continue;
        }

        public: LinkAddressType GetTreeRoot()
                {
                    return this->object().GetTreeRoot();
                };

        public: LinkAddressType GetBasePartValue(LinkAddressType link)
                {
                    return this->object().GetBasePartValue(link);
                };

        public: bool FirstIsToTheRightOfSecond(LinkAddressType source, LinkAddressType target, LinkAddressType rootSource, LinkAddressType rootTarget)
                {
                    return this->object().FirstIsToTheRightOfSecond(source, target, rootSource, rootTarget);
                };

        public: bool FirstIsToTheLeftOfSecond(LinkAddressType source, LinkAddressType target, LinkAddressType rootSource, LinkAddressType rootTarget)
                {
                    return this->object().FirstIsToTheLeftOfSecond(source, target, rootSource, rootTarget);
                };

        public: auto&& GetHeaderReference() const
        {
            return *reinterpret_cast<LinksHeader<LinkAddressType>*>(Header);
        }

        protected: RawLinkDataPart<LinkAddressType>& GetLinkDataPartReference(LinkAddressType link) { return *reinterpret_cast<RawLinkDataPart<LinkAddressType>*>(LinksDataParts + (RawLinkDataPart<LinkAddressType>::SizeInBytes * (link))); }

        protected: RawLinkIndexPart<LinkAddressType>& GetLinkIndexPartReference(LinkAddressType link) { *reinterpret_cast<RawLinkIndexPart<LinkAddressType>*>(LinksIndexParts + (RawLinkIndexPart<LinkAddressType>::SizeInBytes * (link))); }

        protected: auto GetLinkValues(LinkAddressType linkIndex)
        {
            auto& link = GetLinkDataPartReference(linkIndex);
            return LinkType(linkIndex, link.Source, link.Target);
        }

        public: bool FirstIsToTheLeftOfSecond(LinkAddressType first, LinkAddressType second)
        {
            auto& firstLink = this->GetLinkDataPartReference(first);
            auto& secondLink = this->GetLinkDataPartReference(second);
            return this->FirstIsToTheLeftOfSecond(firstLink.Source, firstLink.Target, secondLink.Source, secondLink.Target);
        }

        public: bool FirstIsToTheRightOfSecond(LinkAddressType first, LinkAddressType second)
        {
            auto& firstLink = this->GetLinkDataPartReference(first);
            auto& secondLink = this->GetLinkDataPartReference(second);
            return this->FirstIsToTheRightOfSecond(firstLink.Source, firstLink.Target, secondLink.Source, secondLink.Target);
        }

        public: LinkAddressType operator[](LinkAddressType index)
        {
            auto root = GetTreeRoot();
            if (GreaterOrEqualThan(index, GetSize(root)))
            {
                return 0;
            }
            while (!EqualToZero(root))
            {
                auto left = GetLeftOrDefault(root);
                auto leftSize = GetSizeOrZero(left);
                if (LessThan(index, leftSize))
                {
                    root = left;
                    continue;
                }
                if (AreEqual(index, leftSize))
                {
                    return root;
                }
                root = GetRightOrDefault(root);
                index = Subtract(index, Increment(leftSize));
            }
            return 0;

        }

        public: LinkAddressType Search(LinkAddressType source, LinkAddressType target)
        {
            auto root = this->GetTreeRoot();
            while (root != 0)
            {
                auto& rootLink = this->GetLinkDataPartReference(root);
                auto rootSource = rootLink.Source;
                auto rootTarget = rootLink.Target;
                if (this->FirstIsToTheLeftOfSecond(source, target, rootSource, rootTarget))
                {
                    root = this->GetLeftOrDefault(root);
                }
                else if (this->FirstIsToTheRightOfSecond(source, target, rootSource, rootTarget))
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

        public: LinkAddressType CountUsages(LinkAddressType link)
        {
            auto root = this->GetTreeRoot();
            auto total = this->GetSize(root);
            auto totalRightIgnore = 0;
            while (root != 0)
            {
                auto base = this->GetBasePartValue(root);
                if (base <= link)
                {
                    root = this->GetRightOrDefault(root);
                }
                else
                {
                    totalRightIgnore = totalRightIgnore + (this->GetRightSize(root) + 1);
                    root = this->GetLeftOrDefault(root);
                }
            }
            root = this->GetTreeRoot();
            auto totalLeftIgnore = 0;
            while (root != 0)
            {
                auto base = this->GetBasePartValue(root);
                if (base >= link)
                {
                    root = this->GetLeftOrDefault(root);
                }
                else
                {
                    totalLeftIgnore = totalLeftIgnore + (this->GetLeftSize(root) + 1);
                    root = this->GetRightOrDefault(root);
                }
            }
            return (total - totalRightIgnore) - totalLeftIgnore;
        }

        public: LinkAddressType EachUsage(LinkAddressType base, auto&& handler) { return this->EachUsageCore(base, this->GetTreeRoot(), handler); }

        private: LinkAddressType EachUsageCore(LinkAddressType base, LinkAddressType link, auto&& handler)
        {
            if (link == 0)
            {
                return Continue;
            }
            auto linkBasePart = this->GetBasePartValue(link);
            if (linkBasePart > (base))
            {
                if ((this->EachUsageCore(base) == (this->GetLeftOrDefault(link), handler), Break))
                {
                    return Break;
                }
            }
            else if (this->LessThan(linkBasePart, base))
            {
                if ((this->EachUsageCore(base) == (this->GetRightOrDefault(link), handler), Break))
                {
                    return Break;
                }
            }
            else
            {
                if (handler(this->GetLinkValues(link)) == (Break))
                {
                    return Break;
                }
                if ((this->EachUsageCore(base) == (this->GetLeftOrDefault(link), handler), Break))
                {
                    return Break;
                }
                if ((this->EachUsageCore(base) == (this->GetRightOrDefault(link), handler), Break))
                {
                    return Break;
                }
            }
            return Continue;
        }
        };
}
