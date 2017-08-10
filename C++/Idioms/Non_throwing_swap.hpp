class UserDefined 
{
    String str;
  public:
    void swap (UserDefined & u) // throw () 
    { 
      std::swap (str, u.str); 
    }
};

namespace std
{
  // Full specializations of the templates in std namespace can be added in std namespace.
  template <>
  void swap (UserDefined & u1, UserDefined & u2) // throw ()
  {
    u1.swap (u2);
  }
}

class Myclass
{
    UserDefined u;
    char * name;
  public:
    void swap (Myclass & m) // throw ()
    {
      std::swap (u, m.u);       // cascading use of the idiom due to uniformity
      std::swap (name, m.name); // Ditto here
    }   
}

namespace std
{
   // Full specializations of the templates in std namespace can be added in std namespace.
   template <> 
   void swap (Myclass & m1, Myclass & m2) // throw ()
   {
     m1.swap (m2);
   }
};