import Home from '../views/Home.vue'
import Login from '../views/Login.vue'

export default [
  { path: "*", redirect: "/home" },
  {
     meta: {
      public: true // you're saying if this page is public or not (in this case it is :))
     },
     path: '/home', // the path of this new page
     component: Home, // the one you imported
     name: 'home'
  },
  {
    meta: {
     public: true // you're saying if this page is public or not (in this case it is :))
    },
    path: '/login', // the path of this new page
    component: Login, // the one you imported
    name: 'about'
 }
]