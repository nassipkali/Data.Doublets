﻿namespace Platform::Data::Doublets::Tests
{
    template <typename TLink>
    static void Using(auto&& action)
    {
        using namespace Platform::Memory;
        using namespace Platform::Data::Doublets::Memory::United::Generic;
        using namespace Platform::Data::Doublets::Memory::United;
        using namespace Platform::Collections;
//        HeapResizableDirectMemory memory {};
//        UnitedMemoryLinks<TLink, HeapResizableDirectMemory> storage { memory };
//        action(storage);
        std::string tempFilePath { std::tmpnam(nullptr) };
        Expects(!Collections::IsWhiteSpace(tempFilePath));
        std::cout << "\n\ntempFilePath: " << tempFilePath << std::endl;
        try
        {
            Ffi::UnitedMemoryLinks<TLink> ffiStorage {tempFilePath };
            action(ffiStorage);
        }
        catch (...)
        {
            std::remove(tempFilePath.c_str());
            throw;
        }
        std::remove(tempFilePath.c_str());
    }
    TEST(GenericLinksTests, CrudTest)
    {
        Using<std::uint8_t>([] (auto&& storage) { TestCrudOperations<std::uint8_t>(storage); });
        Using<std::uint16_t>([] (auto&& storage) { TestCrudOperations<std::uint16_t>(storage); });
        Using<std::uint32_t>([] (auto&& storage) { TestCrudOperations<std::uint32_t>(storage); });
        Using<std::uint64_t>([] (auto&& storage) { TestCrudOperations<std::uint64_t>(storage); });
    }

    TEST(GenericLinksTests, RawNumbersCrudTest)
    {
        Using<std::uint8_t>([] (auto&& storage) { TestRawNumbersCrudOperations<std::uint8_t>(storage); });
        Using<std::uint16_t>([] (auto&& storage) { TestRawNumbersCrudOperations<std::uint16_t>(storage); });
        Using<std::uint32_t>([] (auto&& storage) { TestRawNumbersCrudOperations<std::uint32_t>(storage); });
        Using<std::uint64_t>([] (auto&& storage) { TestRawNumbersCrudOperations<std::uint64_t>(storage); });
    }

//    TEST(GenericLinksTests, MultipleRandomCreationsAndDeletionsTest)
//    {
//        Using<std::uint8_t>([] (auto&& storage){
//        auto decoratedStorage = DecorateWithAutomaticUniquenessAndUsagesResolution<std::uint8_t>(storage);
//        TestMultipleRandomCreationsAndDeletions<std::uint8_t>(decoratedStorage, 16);
//        });
//        Using<std::uint16_t>([] (auto&& storage){
//            auto decoratedStorage = DecorateWithAutomaticUniquenessAndUsagesResolution<std::uint16_t>(storage);
//            TestMultipleRandomCreationsAndDeletions<std::uint16_t>(decoratedStorage, 100);
//        });
//        Using<std::uint32_t>([] (auto&& storage){
//            auto decoratedStorage = DecorateWithAutomaticUniquenessAndUsagesResolution<std::uint32_t>(storage);
//            TestMultipleRandomCreationsAndDeletions<std::uint32_t>(decoratedStorage, 100);
//        });
//        Using<std::uint64_t>([] (auto&& storage){
//            auto decoratedStorage = DecorateWithAutomaticUniquenessAndUsagesResolution<std::uint64_t>(storage);
//            TestMultipleRandomCreationsAndDeletions<std::uint64_t>(decoratedStorage, 100);
//        });
//    }

   TEST(GenericLinksTests, MultipleRandomCreationsAndDeletionsTest)
   {
       Using<std::uint8_t>([] (auto&& storage){
       TestMultipleRandomCreationsAndDeletions<std::uint8_t>(storage, 16);
       });
       Using<std::uint16_t>([] (auto&& storage){
           TestMultipleRandomCreationsAndDeletions<std::uint16_t>(storage, 100);
       });
       Using<std::uint32_t>([] (auto&& storage){
           TestMultipleRandomCreationsAndDeletions<std::uint32_t>(storage, 100);
       });
       Using<std::uint64_t>([] (auto&& storage){
           TestMultipleRandomCreationsAndDeletions<std::uint64_t>(storage, 100);
       });
   }
}
