﻿namespace Platform::Data::Doublets::Memory::Split::Generic {
  template <typename TLinksOptions>
  class ExternalLinksSourcesRecursionlessSizeBalancedTreeMethods : public ExternalLinksRecursionlessSizeBalancedTreeMethodsBase<ExternalLinksSourcesRecursionlessSizeBalancedTreeMethods<TLinksOptions>, TLinksOptions> {
    using base = ExternalLinksRecursionlessSizeBalancedTreeMethodsBase<ExternalLinksSourcesRecursionlessSizeBalancedTreeMethods<TLinksOptions>, TLinksOptions>;

   public:
    using LinksOptionsType = TLinksOptions;

   public:
    using LinkAddressType = typename LinksOptionsType::LinkAddressType;
    using LinkType = typename LinksOptionsType::LinkType;
    using WriteHandlerType = typename LinksOptionsType::WriteHandlerType;
    using ReadHandlerType = typename LinksOptionsType::ReadHandlerType;

   public:
    static constexpr auto Constants = LinksOptionsType::Constants;

   public:
    ExternalLinksSourcesRecursionlessSizeBalancedTreeMethods(std::byte* linksDataParts, std::byte* linksIndexParts, std::byte* header) : base(linksDataParts, linksIndexParts, header) {}

   public:
    LinkAddressType* GetLeftReference(LinkAddressType node) { return &(this->GetLinkIndexPartReference(node).LeftAsSource); }

   public:
    LinkAddressType* GetRightReference(LinkAddressType node) { return &(this->GetLinkIndexPartReference(node).RightAsSource); }

   public:
    LinkAddressType GetLeft(LinkAddressType node) { return this->GetLinkIndexPartReference(node).LeftAsSource; }

   public:
    LinkAddressType GetRight(LinkAddressType node) { return this->GetLinkIndexPartReference(node).RightAsSource; }

   public:
    void SetLeft(LinkAddressType node, LinkAddressType left) { this->GetLinkIndexPartReference(node).LeftAsSource = left; }

   public:
    void SetRight(LinkAddressType node, LinkAddressType right) { this->GetLinkIndexPartReference(node).RightAsSource = right; }

   public:
    LinkAddressType GetSize(LinkAddressType node) { return this->GetLinkIndexPartReference(node).SizeAsSource; }

   public:
    void SetSize(LinkAddressType node, LinkAddressType size) { this->GetLinkIndexPartReference(node).SizeAsSource = size; }

   public:
    LinkAddressType GetTreeRoot() { return this->GetHeaderReference().RootAsSource; }

   public:
    LinkAddressType GetBasePartValue(LinkAddressType link) { return this->GetLinkDataPartReference(link).Source; }

   public:
    bool FirstIsToTheLeftOfSecond(LinkAddressType firstSource, LinkAddressType firstTarget, LinkAddressType secondSource, LinkAddressType secondTarget) { return (firstSource < secondSource) || (firstSource == secondSource && (firstTarget < secondTarget)); }
    using base::FirstIsToTheLeftOfSecond;

   public:
    bool FirstIsToTheRightOfSecond(LinkAddressType firstSource, LinkAddressType firstTarget, LinkAddressType secondSource, LinkAddressType secondTarget) { return firstSource > secondSource || (firstSource == secondSource && firstTarget > secondTarget); }
    using base::FirstIsToTheRightOfSecond;

   public:
    void ClearNode(LinkAddressType node) {
      auto& link = this->GetLinkIndexPartReference(node);
      link.LeftAsSource = 0;
      link.RightAsSource = 0;
      link.SizeAsSource = 0;
    }
  };
}  // namespace Platform::Data::Doublets::Memory::Split::Generic
