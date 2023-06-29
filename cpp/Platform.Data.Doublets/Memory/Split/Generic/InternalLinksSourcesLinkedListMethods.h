﻿namespace Platform::Data::Doublets::Memory::Split::Generic {
  template <typename TLinksOptions>
  class InternalLinksSourcesLinkedListMethods : public Platform::Collections::Methods::Lists::RelativeCircularDoublyLinkedListMethods<InternalLinksSourcesLinkedListMethods<TLinksOptions>, typename TLinksOptions::LinkAddressType> {
   public:
    using LinksOptionsType = TLinksOptions;
    using LinkAddressType = typename LinksOptionsType::LinkAddressType;
    using LinkType = typename LinksOptionsType::LinkType;
    using WriteHandlerType = typename LinksOptionsType::WriteHandlerType;
    using ReadHandlerType = typename LinksOptionsType::ReadHandlerType;

   public:
    static constexpr auto Constants = LinksOptionsType::Constants;

   private:
    std::byte* _linksDataParts;
    std::byte* _linksIndexParts;

   public:
    LinkAddressType Break = Constants.Break;
    LinkAddressType Continue = Constants.Continue;

   public:
    InternalLinksSourcesLinkedListMethods(std::byte* linksDataParts, std::byte* linksIndexParts) {
      _linksDataParts = linksDataParts;
      _linksIndexParts = linksIndexParts;
    }

   public:
    const RawLinkDataPart<LinkAddressType>& GetLinkDataPartReference(LinkAddressType link) const {
      return *reinterpret_cast<RawLinkDataPart<LinkAddressType>*>(_linksDataParts + (RawLinkDataPart<LinkAddressType>::SizeInBytes * link));
    }

   public:
    RawLinkDataPart<LinkAddressType>& GetLinkDataPartReference(LinkAddressType link) {
      return *reinterpret_cast<RawLinkDataPart<LinkAddressType>*>(_linksDataParts + (RawLinkDataPart<LinkAddressType>::SizeInBytes * link));
    }

   public:
    const RawLinkIndexPart<LinkAddressType>& GetLinkIndexPartReference(LinkAddressType link) const {
      return *reinterpret_cast<RawLinkIndexPart<LinkAddressType>*>(_linksDataParts + (RawLinkIndexPart<LinkAddressType>::SizeInBytes * link));
    }

   public:
    RawLinkIndexPart<LinkAddressType>& GetLinkIndexPartReference(LinkAddressType link) {
      return *reinterpret_cast<RawLinkIndexPart<LinkAddressType>*>(_linksDataParts + (RawLinkIndexPart<LinkAddressType>::SizeInBytes * link));
    }

   public:
    LinkAddressType GetFirst(LinkAddressType head) {
      return this->GetLinkIndexPartReference(head).RootAsSource;
    }

   public:
    LinkAddressType GetLast(LinkAddressType head) {
      auto first = this->GetLinkIndexPartReference(head).RootAsSource;
      if (0 == first) {
        return first;
      } else {
        return this->GetPrevious(first);
      }
    }

   public:
    LinkAddressType GetPrevious(LinkAddressType element) {
      return this->GetLinkIndexPartReference(element).LeftAsSource;
    }

   public:
    LinkAddressType GetNext(LinkAddressType element) {
      return this->GetLinkIndexPartReference(element).RightAsSource;
    }

   public:
    LinkAddressType GetSize(LinkAddressType head) {
      return this->GetLinkIndexPartReference(head).SizeAsSource;
    }

   public:
    void SetFirst(LinkAddressType head, LinkAddressType element) {
      this->GetLinkIndexPartReference(head).RootAsSource = element;
    }

   public:
    void SetLast(LinkAddressType head, LinkAddressType element) {}

   public:
    void SetPrevious(LinkAddressType element, LinkAddressType previous) {
      this->GetLinkIndexPartReference(element).LeftAsSource = previous;
    }

   public:
    void SetNext(LinkAddressType element, LinkAddressType next) {
      this->GetLinkIndexPartReference(element).RightAsSource = next;
    }

   public:
    void SetSize(LinkAddressType head, LinkAddressType size) {
      this->GetLinkIndexPartReference(head).SizeAsSource = size;
    }

   public:
    LinkAddressType CountUsages(LinkAddressType head) {
      return this->GetSize(head);
    }

   public:
    Interfaces::CArray auto GetLinkValues(LinkAddressType linkIndex) {
      auto& link = this->GetLinkDataPartReference(linkIndex);
      return Link{linkIndex, link.Source, link.Target};
    }

   public:
    LinkAddressType EachUsage(LinkAddressType source, const ReadHandlerType& handler) {
      auto current = this->GetFirst(source);
      auto first = current;
      while (current != 0) {
        if (handler(this->GetLinkValues(current)) == (Break)) {
          return Break;
        }
        current = this->GetNext(current);
        if (current == first) {
          return Continue;
        }
      }
      return Continue;
    }
  };
}  // namespace Platform::Data::Doublets::Memory::Split::Generic
