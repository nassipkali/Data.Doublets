﻿namespace Platform::Data::Doublets::Memory::Split::Generic {
  template <typename TLinksOptions>
  class InternalLinksTargetsSizeBalancedTreeMethods : public InternalLinksSizeBalancedTreeMethodsBase<InternalLinksTargetsSizeBalancedTreeMethods<TLinksOptions>, TLinksOptions> {
   public:
    using LinksOptionsType = TLinksOptions;
    using LinkAddressType = typename LinksOptionsType::LinkAddressType;
    using LinkType = typename LinksOptionsType::LinkType;
    using WriteHandlerType = typename LinksOptionsType::WriteHandlerType;
    using ReadHandlerType = typename LinksOptionsType::ReadHandlerType;

   public:
    static constexpr auto Constants = LinksOptionsType::Constants;
    using base = InternalLinksSizeBalancedTreeMethodsBase<InternalLinksTargetsSizeBalancedTreeMethods<TLinksOptions>, TLinksOptions>;

   public:
    InternalLinksTargetsSizeBalancedTreeMethods(std::byte* linksDataParts, std::byte* linksIndexParts, std::byte* header) : base(linksDataParts, linksIndexParts, header) {}

   public:
    LinkAddressType* GetLeftReference(LinkAddressType node) {
      return &(this->GetLinkIndexPartReference(node).LeftAsTarget);
    }

   public:
    LinkAddressType* GetRightReference(LinkAddressType node) {
      return &(this->GetLinkIndexPartReference(node).RightAsTarget);
    }

   public:
    LinkAddressType GetLeft(LinkAddressType node) {
      return this->GetLinkIndexPartReference(node).LeftAsTarget;
    }

   public:
    LinkAddressType GetRight(LinkAddressType node) {
      return this->GetLinkIndexPartReference(node).RightAsTarget;
    }

   public:
    void SetLeft(LinkAddressType node, LinkAddressType left) {
      this->GetLinkIndexPartReference(node).LeftAsTarget = left;
    }

   public:
    void SetRight(LinkAddressType node, LinkAddressType right) {
      this->GetLinkIndexPartReference(node).RightAsTarget = right;
    }

   public:
    LinkAddressType GetSize(LinkAddressType node) {
      return this->GetLinkIndexPartReference(node).SizeAsTarget;
    }

   public:
    void SetSize(LinkAddressType node, LinkAddressType size) {
      this->GetLinkIndexPartReference(node).SizeAsTarget = size;
    }

   public:
    LinkAddressType GetTreeRoot(LinkAddressType link) {
      return this->GetLinkIndexPartReference(link).RootAsTarget;
    }

   public:
    LinkAddressType GetBasePartValue(LinkAddressType link) {
      return this->GetLinkDataPartReference(link).Target;
    }

   public:
    LinkAddressType GetKeyPartValue(LinkAddressType link) {
      return this->GetLinkDataPartReference(link).Source;
    }

   public:
    void ClearNode(LinkAddressType node) {
      auto& link = this->GetLinkIndexPartReference(node);
      link.LeftAsTarget = 0;
      link.RightAsTarget = 0;
      link.SizeAsTarget = 0;
    }

   public:
    LinkAddressType Search(LinkAddressType source, LinkAddressType target) {
      return this->SearchCore(this->GetTreeRoot(target), source);
    }
  };
}  // namespace Platform::Data::Doublets::Memory::Split::Generic
