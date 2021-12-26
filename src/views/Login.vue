<template>
  <div>
    <h1
      v-if="!this.$store.state.isLogged"
      @click="login"
    >
      Faça seu login
    </h1>
    <h1
      v-if="this.$store.state.isLogged"
      @click="logout"
    >
      Faça seu logout
    </h1>
  </div>
</template>
<script>
// import router from "../router";

export default {
    name: "About",
    methods: {
        login() {
            alert('Olhe o log e vc fez login')
            this.$store.dispatch("setLogged", true);
            // router.push("/home");
        },
        logout() {
            alert('Olhe o log e vc fez login')

            this.$store.dispatch("setLogged", false);
            // router.push("/home");
        }
    },
};
</script>

<style scoped lang="scss">

</style>